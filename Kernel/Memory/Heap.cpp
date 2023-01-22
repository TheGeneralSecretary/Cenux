#include <Kernel/Memory/Heap.h>
#include <Kernel/Errno.h>
#include <Kernel/KString.h>
#include <Kernel/KPrintf.h>

#define HEAP_ALIGN_CHECK(addr, blocksize) (((uint32_t)addr % blocksize) == 0)
#define HEAP_ALIGN_SIZE(size, blocksize) (size % blocksize ? (size - (size % blocksize)) + blocksize : size)
#define HEAP_BLOCK_IS_ALLOCATED(block) ((block & HEAP_BLOCK_TYPE) == HEAP_BLOCK_ALLOCATED)
#define HEAP_BLOCK_IS_FREE(block) ((block & HEAP_BLOCK_TYPE) == HEAP_BLOCK_FREE)

/* HEAP_BLOCK_START, HEAP_BLOCK_CONTIGUOUS, 0, 0, HEAP_BLOCK_TYPE_4BIT */
#define HEAP_BLOCK_START 0x80
#define HEAP_BLOCK_CONTIGUOUS 0x40
#define HEAP_BLOCK_ALLOCATED 0x01
#define HEAP_BLOCK_FREE 0x00
#define HEAP_BLOCK_TYPE 0x0f

namespace Kernel
{
	namespace Memory
	{
		int32_t Heap::Init(uint32_t* startAddr, uint32_t* endAddr, uint32_t blockSize, uint32_t heapSize)
		{
			KPrintf("Initializing Heap...\n");

			if (!HEAP_ALIGN_CHECK(startAddr, blockSize) || !HEAP_ALIGN_CHECK(endAddr, blockSize))
				return -EINVAL;

			m_HeapSize = heapSize;
			m_EndAddress = endAddr;
			m_BlockSize = blockSize;
			m_BlockCount = m_HeapSize / m_BlockSize;
			m_Blocks = (uint8_t*)(startAddr);
			m_StartAddress = (uint32_t*)(((uint8_t*)startAddr) + m_BlockCount); // Reserved space for block table

			if (!VerifyBlockTable())
				return false;

			memset(m_Blocks, 0x0, m_BlockCount);
			return 0;
		}

		uint32_t* Heap::Malloc(uint32_t size)
		{
			uint32_t alignedSize = HEAP_ALIGN_SIZE(size, m_BlockSize);
			uint32_t totalBlocks = alignedSize / m_BlockSize;
			return MallocBlocks(totalBlocks);
		}

		void Heap::Free(uint32_t* ptr)
		{
			SetBlocksFree(AddressToBlock(ptr));
		}

		bool Heap::VerifyBlockTable()
		{
			uint32_t tableSize = (m_EndAddress - m_StartAddress);
			uint32_t totalBlock = tableSize / m_BlockSize;
			return (m_BlockCount == totalBlock);
		}

		uint32_t* Heap::MallocBlocks(uint32_t count)
		{
			uint32_t* addr = 0;
			
			int32_t startBlock = GetStartBlock(count);
			if (startBlock < 0)
				return addr;

			SetBlocksAllocated(startBlock, count);

			addr = BlockToAddress(startBlock);
			return addr;
		}

		int32_t Heap::GetStartBlock(uint32_t totalBlocks)
		{
			int32_t startBlock = -1;
			uint32_t currentBlock = 0;

			for (uint32_t i = 0; i < m_BlockSize; i++)
			{
				if (!HEAP_BLOCK_IS_FREE(m_Blocks[i]))
				{
					startBlock = -1;
					currentBlock = 0;
					continue;
				}

				if (startBlock == -1)
					startBlock = i;

				currentBlock++;
				if (currentBlock == totalBlocks)
					break;
			}

			if (startBlock == -1)
				return -ENOMEM;

			return startBlock;
		}

		void Heap::SetBlocksAllocated(uint32_t startBlock, uint32_t totalBlocks)
		{
			uint8_t block = HEAP_BLOCK_START | HEAP_BLOCK_ALLOCATED;
			if (totalBlocks > 1)
				block |= HEAP_BLOCK_CONTIGUOUS;

			uint32_t endBlock = (startBlock + totalBlocks) - 1;
			for (uint32_t i = startBlock; i <= endBlock; i++)
			{
				m_Blocks[i] = block;
				block = HEAP_BLOCK_ALLOCATED;
				if (i != endBlock - i)
					block |= HEAP_BLOCK_CONTIGUOUS;
			}
		}

		void Heap::SetBlocksFree(uint32_t startBlock)
		{
			for (uint32_t i = startBlock; i < m_BlockSize; i++)
			{
				uint8_t block = m_Blocks[i];
				m_Blocks[i] = HEAP_BLOCK_FREE;
				if (!(block & HEAP_BLOCK_CONTIGUOUS))
					break;
			}
		}

		uint32_t* Heap::BlockToAddress(uint32_t block)
		{
			return (m_StartAddress + (block * m_BlockSize));
		}

		uint32_t Heap::AddressToBlock(uint32_t* address)
		{
			return ((uint32_t)address - (uint32_t)m_StartAddress) / m_BlockSize;
		}
	}
}
