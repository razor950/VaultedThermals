/*!
@file VT_SwapChain.hpp

@brief Vaulted Thermals: Swap Chain

@details
<a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#_wsi_swapchain">Specification</a> 
*/



#pragma once



// VT
#include "VT_Vaults.hpp"
#include "VT_Platform.hpp"
#include "VT_Enums.hpp"
#include "VT_Backend.hpp"
#include "VT_Types.hpp"
#include "VT_Constants.hpp"
#include "VT_Memory_Backend.hpp"
#include "VT_PhysicalDevice.hpp"
#include "VT_Initialization.hpp"
#include "VT_LogicalDevice.hpp"
#include "VT_Memory.hpp"
#include "VT_Sampler.hpp"
#include "VT_Resource.hpp"
#include "VT_SyncAndCacheControl.hpp"
#include "VT_Shaders.hpp"
#include "VT_Pipelines.hpp"
#include "VT_RenderPass.hpp"
#include "VT_Command.hpp"
#include "VT_Surface.hpp"



#ifndef VT_Option__Use_Long_Namespace
/**
@namespace VaultedThermals

@brief Main library namespace for Vaulted Thermals (Vulkan Wrapper)

@details For long namespace: #define VT_Option__Use_Long_Namespace
*/
namespace VT
#else
/**
@namespace VaultedThermals

@brief Main library namespace for Vaulted Thermals (Vulkan Wrapper)

@details VT_Option__Use_Long_Namespace in use.
*/
namespace VaultedThermals
#endif
{
	namespace V1
	{
		/**
		@addtogroup Vault_1
		@{
		*/

		/**
		 * @brief A queue of images that can be presented to a surface.
		 * 
		 * @details
		 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#_wsi_swapchain">Specification</a> 
		 */
		struct Swapchain
		{
			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkSwapchainKHR">Specification</a>  */
			using Handle = VkSwapchainKHR;

			/**
			 * @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkSwapchainCreateInfoKHR.html">Specification</a> .
			 */
			struct CreateInfo : V0::VKStruct_Base<VkSwapchainCreateInfoKHR, EStructureType::SwapChain_CreateInfo_KHR>
			{
				using ECreateFlag = ESwapchainCreateFlag;

				/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkSwapchainCreateFlagsKHR">Specification</a>  */
				using CreateFlags = Bitmask<ECreateFlag, VkSwapchainCreateFlagsKHR >;

				      EType                 SType                ;
				const void*                 Next                 ;
				      CreateFlags           Flags                ;
				      Surface::Handle       Surface              ; 
				      uint32                MinImageCount        ;
				      EFormat               ImageFormat          ;
				      EColorSpace           ImageColorSpace      ;
				      Extent2D              ImageExtent          ;
				      uint32                ImageArrayLayers     ;
				      Image::UsageFlags	    ImageUsage           ;
				      ESharingMode          ImageSharingMode     ;
				      uint32                QueueFamilyIndexCount;
				const uint32*               QueueFamilyIndices   ;
				      ESurfaceTransformFlag PreTransform         ;
				      ECompositeAlpha       CompositeAlpha       ;
				      EPresentationMode     PresentationMode     ;
				      Bool                  Clipped              ;
				      Handle                OldSwapchain         ;
			};

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkPresentInfoKHR">Specification</a>  */
			struct PresentationInfo : V0::VKStruct_Base<VkPresentInfoKHR, EStructureType::PresentInfo_KHR>
			{
				      EType              SType             ;
				const void*              Next              ;
				      uint32             WaitSemaphoreCount;
				const Semaphore::Handle* WaitSemaphores    ;
				      uint32             SwapchainCount    ;
				const Handle*            Swapchains        ;
				const uint32*            ImageIndices      ;
				      EResult*           Results           ;
			};

			/**
			 * @brief
			 * 
			 * @details <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#vkAcquireNextImageKHR">Specification</a>
			 * 
			 * \param _device
			 * \param _swapchain
			 * \param _timeout
			 * \param _semaphore
			 * \param _fence
			 * \param _imageIndex
			 * \return 
			 */
			static EResult AcquireNextImage
			(
				LogicalDevice::Handle _device    ,
				Handle                _swapchain ,
				uInt64                _timeout   ,
				Semaphore::Handle     _semaphore ,
				Fence::Handle         _fence     ,
				uint32&               _imageIndex
			)
			{
				return EResult(vkAcquireNextImageKHR(_device, _swapchain, _timeout, _semaphore, _fence, &_imageIndex));
			}

			/**
			 * @brief Create a swapchain.
			 * 
			 * @details
			 * If the oldSwapchain parameter of pCreateInfo is a valid swapchain, which has exclusive full-screen access, that access is released from oldSwapchain. 
			 * If the command succeeds in this case, the newly created swapchain will automatically acquire exclusive full-screen access from oldSwapchain.
			 * 
			 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#vkCreateSwapchainKHR">link text</a> 
			 * 
			 * \param _deviceHandle
			 * \param _creationSpecification
			 * \param _allocator
			 * \param _swapChain
			 * \return 
			 */
			static EResult Create
			(
				      LogicalDevice::Handle        _deviceHandle,
				const CreateInfo&                  _info        ,
				const Memory::AllocationCallbacks* _allocator   ,
				      Handle&                      _swapChain
			)
			{
				return EResult(vkCreateSwapchainKHR(_deviceHandle, _info, _allocator->operator const VkAllocationCallbacks*(), &_swapChain));
			};

			/**
			 * @brief Destroy a swapchain object.
			 * 
			 * @details
			 * The application must not destroy a swapchain until after completion of all outstanding operations on images that were acquired from the swapchain. 
			 * swapchain and all associated VkImage handles are destroyed, and must not be acquired or used any more by the application.
			 * 
			 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#vkDestroySwapchainKHR">Specification</a> 
			 * 
			 * \param _deviceHandle
			 * \param _swapChainToDestroy
			 * \param _allocator
			 */
			static void Destroy(LogicalDevice::Handle _deviceHandle, Handle _swapChainToDestroy, const Memory::AllocationCallbacks* _allocator)
			{
				vkDestroySwapchainKHR(_deviceHandle, _swapChainToDestroy, _allocator->operator const VkAllocationCallbacks*());
			}

			/**
			 * @brief Obtain the array of presentable images associated with a swapchain.
			 * 
			 * @details
			 * If pSwapchainImages is NULL, then the number of presentable images for swapchain is returned in pSwapchainImageCount. 
			 * Otherwise, pSwapchainImageCount must point to a variable set by the user to the number of elements in the pSwapchainImages array, 
			 * and on return the variable is overwritten with the number of structures actually written to pSwapchainImages.
			 * 
			 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#vkGetSwapchainImagesKHR">Specification</a> 
			 * 
			 * \param _deviceHandle
			 * \param _swapChain
			 * \param _numImages
			 * \param _images
			 * \return 
			 */
			static EResult QueryImages(LogicalDevice::Handle _deviceHandle, Handle _swapChain, uint32& _numImages, Image::Handle* _imagesContainer)
			{
				return EResult(vkGetSwapchainImagesKHR(_deviceHandle, _swapChain, &_numImages, _imagesContainer));
			}
		};

		/** @} */
	}

	namespace V2
	{
		/**
		@addtogroup Vault_2
		@{
		*/

		struct Swapchain : V1::Swapchain
		{
			using Parent = V1::Swapchain;

			struct CreateInfo : Parent::CreateInfo
			{
				CreateInfo()
				{
					SType = STypeEnum;
					Next  = nullptr  ;
				}
			};

			struct PresentationInfo : Parent::PresentationInfo
			{
				PresentationInfo()
				{
					SType = STypeEnum;
					Next  = nullptr  ;
				}
			};
			
			static EResult Create
			(
				      LogicalDevice::Handle _deviceHandle,
				const CreateInfo&           _info        ,
				      Handle&               _swapChain
			)
			{
				return Parent::Create(_deviceHandle, _info, Memory::DefaultAllocator, _swapChain);
			}

			using Parent::Create;

			static void Destroy(LogicalDevice::Handle _deviceHandle, Handle _swapChainToDestroy)
			{
				Parent::Destroy(_deviceHandle, _swapChainToDestroy, Memory::DefaultAllocator);
			}

			using Parent::Destroy;

			/**
			 * @brief Provides all presentable images with the swapchain.
			 * 
			 * \param _deviceHandle
			 * \param _swapChain
			 * \param _images
			 * \return 
			 */
			static EResult GetImages
			(
				LogicalDevice::Handle        _deviceHandle,
				Handle                       _swapChain   ,
				DynamicArray<Image::Handle>* _images
			)
			{
				uint32 numImages;

				EResult result = QueryImages(_deviceHandle, _swapChain, numImages, nullptr);

				if (result != EResult::Success) return result;

				_images->resize(numImages);
					
				result = QueryImages(_deviceHandle, _swapChain, numImages, _images->data());

				return result;
			}
		};

		/** @} */
	}

	namespace V3
	{
		/**
		@addtogroup Vault_3
		@{
		*/

		class Swapchain : public V2::Swapchain
		{
		public:

			using Parent = V2::Swapchain;

			EResult AcquireNextImage
			(
				uInt64                _timeout   ,
				Semaphore::Handle     _semaphore ,
				Fence::Handle         _fence     ,
				uint32&               _imageIndex
			)
			{
				return Parent::AcquireNextImage(device, handle, _timeout, _semaphore, _fence, _imageIndex);
			}

			EResult Create
			(
				      LogicalDevice::Handle _deviceHandle,
				const CreateInfo&           _info        
			)
			{
				device    = _deviceHandle;
				info      = _info        ;
				allocator = Memory::DefaultAllocator;

				return Parent::Create(device, info, handle);
			}

			EResult Create
			(
				      LogicalDevice::Handle        _deviceHandle,
				const CreateInfo&                  _info        ,
				const Memory::AllocationCallbacks* _allocator   
			)
			{
				device    = _deviceHandle;
				info      = _info        ;
				allocator = _allocator   ;

				return Parent::Create(device, info, allocator, handle);
			}

			void Destroy()
			{
				Parent::Destroy(device, handle);
			}

			const Handle& GetHandle() const
			{
				return handle;
			}

			EResult GetImages(DynamicArray<Image>& _images)
			{
				uint32 numImages;

				EResult result = QueryImages(numImages, nullptr);

				if (result != EResult::Success) return result;

				_images.resize(numImages);	DynamicArray<Image::Handle> handles(numImages);

				result = QueryImages(numImages, handles.data());

				for (DeviceSize index = 0; index < numImages; index++)
				{
					_images[index].Assign(device, handles[index]);
				}

				return result;
			}

			uint32 GetMinimumImageCount() const
			{
				return info.MinImageCount;
			}

			EResult QueryImages(uint32& _numImages, Image::Handle* _imagesContainer)
			{
				return Parent::QueryImages(device, handle, _numImages, _imagesContainer);
			}

			operator Handle()
			{
				return handle;
			}

			operator Handle() const
			{
				return handle;
			}

			operator const Handle& () const
			{
				return handle;
			}

			bool operator== (const Swapchain& _other)
			{
				return handle == _other.handle;
			}

		protected:

			Handle handle;

			CreateInfo info;

			const Memory::AllocationCallbacks* allocator;

			LogicalDevice::Handle device;
		};

		/** @} */
	}
}
