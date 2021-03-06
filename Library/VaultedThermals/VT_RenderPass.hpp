/*!
@file VT_RenderPass.hpp

@brief Vaulted Thermals: Render Pass

@details

<a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#renderpass">Specification</a> 
*/



#pragma once



// VT
#include "VT_Vaults.hpp"
#include "VT_Platform.hpp"
#include "VT_CPP_STL.hpp"
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
		 * @brief Render passes operate in conjunction with framebuffers. Framebuffers represent a collection of specific memory attachments that a render pass instance uses.
		 * 
		 * @details
		 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#_framebuffers">Specification</a> 
		 */
		struct Framebuffer
		{
			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkFramebuffer">Specification</a>  */
			using Handle = VkFramebuffer;
			
			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkFramebufferCreateFlags">Specification</a>  */
			using CreateFlags = Bitmask<EFrameBufferCreateFlag, VkFramebufferCreateFlags>;

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkFramebufferCreateInfo">Specification</a>  */
			struct CreateInfo : V0::VKStruct_Base<VkFramebufferCreateInfo, EStructureType::Framebuffer_CreateInfo>
			{
				using RenderPass_Handle = VkRenderPass;   // RenderPass::Handle not defined yet. (Defined later in the file)

				      EType              SType          ;
				const void*              Next           ;
				      CreateFlags        Flags          ;
					  RenderPass_Handle  RenderPass     ;
				      uint32             AttachmentCount;
				const ImageView::Handle* Attachments    ;
				      uint32             Width          ;
				      uint32             Height         ;
				      uint32             Layers         ;
			};

			/**
			 * @brief Creates a framebuffer.
			 * 
			 * @details
			 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#vkCreateFramebuffer">Specification</a> 
			 * 
			 * \param _deviceHanle
			 * \param _creationSpec
			 * \param _allocator
			 * \param _framebuffer
			 * \return 
			 */
			static EResult Create
			(
				      LogicalDevice::Handle        _deviceHanle ,
				const CreateInfo&                  _creationSpec,
				const Memory::AllocationCallbacks* _allocator   ,
				      Handle&                      _framebuffer
			)
			{
				return EResult(vkCreateFramebuffer(_deviceHanle, _creationSpec.operator const VkFramebufferCreateInfo*(), _allocator->operator const VkAllocationCallbacks*(), &_framebuffer));
			}

			/**
			 * @brief Destroy a framebuffer.
			 * 
			 * @details
			 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#vkDestroyFramebuffer">Specification</a> 
			 * 
			 * \param _deviceHandle
			 * \param _framebuffer
			 * \param _allocator
			 */
			static void Destroy(LogicalDevice::Handle _deviceHandle, Handle _framebuffer, const Memory::AllocationCallbacks* _allocator)
			{
				vkDestroyFramebuffer(_deviceHandle, _framebuffer, _allocator->operator const VkAllocationCallbacks*());
			}
		};

		/**
		 * @brief A render pass represents a collection of attachments, subpasses, and dependencies between the subpasses, and describes how the attachments are used over the course of the subpasses.
		 * 
		 * @details <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#renderpass">Specification</a> 
		 */
		struct RenderPass
		{
			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkRenderPass">Specification</a>  */
			using Handle = VkRenderPass;

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkAttachmentDescriptionFlags">Specification</a>  */
			using AttachmentDescriptionFlags = Bitmask<EAttachmentDescriptionFlag, VkAttachmentDescriptionFlags>;
			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkSubpassDescriptionFlags">Specification</a>  */
			using SubpassDesriptionFlags     = Bitmask<ESubpassDescriptionFlag   , VkSubpassDescriptionFlags   >;
			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkRenderPassCreateFlags">Specification</a>  */
			using CreateFlags                = Bitmask<EUndefined                , VkRenderPassCreateFlags     >;

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkAttachmentDescription">Specification</a>  */
			struct AttachmentDescription : V0::VKStruct_Base<VkAttachmentDescription>
			{
				AttachmentDescriptionFlags Flags         ;
				EFormat                    Format        ;
				ESampleCount               Samples       ;
				EAttachmentLoadOperation   LoadOp        ;
				EAttachmentStoreOperation  StoreOp       ;
				EAttachmentLoadOperation   StencilLoadOp ;
				EAttachmentStoreOperation  StencilStoreOp;
				EImageLayout               InitialLayout ;
				EImageLayout               FinalLayout   ;
			};

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkAttachmentReference">Specification</a>  */
			struct AttachmentReference : V0::VKStruct_Base<VkAttachmentReference>
			{
				uint32       Attachment;
				EImageLayout Layout    ;
			};

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkRenderPassBeginInfo">Specification</a>  */
			struct BeginInfo : V0::VKStruct_Base<VkRenderPassBeginInfo, EStructureType::RenderPass_BeginInfo>
			{
				      EType               SType          ;
				const void*               Next           ;
				      RenderPass::Handle  RenderPass     ;
				      Framebuffer::Handle Framebuffer    ;
				      Rect2D              RenderArea     ;
				      uint32              ClearValueCount;
				const ClearValue*         ClearValues    ;
			};

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkSubpassDescription">Specification</a>  */
			struct SubpassDescription : V0::VKStruct_Base<VkSubpassDescription>
			{
				      SubpassDesriptionFlags Flags                  ;
				      EPipelineBindPoint     PipelineBindPoint      ;
				      uint32                 InputAttachmentCount   ;
				const AttachmentReference*   InputAttachments       ;
				      uint32                 ColorAttachmentCount   ;
				const AttachmentReference*   ColorAttachments       ;
				const AttachmentReference*   ResolveAttachments     ;
				const AttachmentReference*   DepthStencilAttachment ;
				      uint32                 PreserveAttachmentCount;
				const uint32*                PreserveAttachments    ;
			};

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkSubpassDependency">Specification</a>  */
			struct SubpassDependency : V0::VKStruct_Base<VkSubpassDependency>
			{
				uint32               SourceSubpass        ;
				uint32               DestinationSubpass   ;
				Pipeline::StageFlags SourceStageMask      ;
				Pipeline::StageFlags DestinationStageMask ;
				AccessFlags          SourceAccessMask     ;
				AccessFlags          DestinationAccessMask;
				DependencyFlags      DependencyFlags      ;
			};

			/** @brief <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#VkRenderPassCreateInfo">Specification</a>  */
			struct CreateInfo : V0::VKStruct_Base<VkRenderPassCreateInfo, EStructureType::RenderPass_CreateInfo>
			{
				      EType                  SType          ;
				const void*                  Next           ;
				      CreateFlags            Flags          ;
				      uint32                 AttachmentCount;
				const AttachmentDescription* Attachments    ;
				      uint32                 SubpassCount   ;
				const SubpassDescription*     Subpasses     ;
				      uint32                 DependencyCount;
				const SubpassDependency*     Dependencies   ;
			};

			/**
			 * @brief Create a render pass.
			 * 
			 * @details
			 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#renderpass-creation">Specification</a> 
			 * 
			 * \param _deviceHandle
			 * \param _createInfo
			 * \param _allocator
			 * \param _renderPass
			 * \return 
			 */
			static EResult Create
			(
				      LogicalDevice::Handle        _deviceHandle,
				const CreateInfo&                  _createInfo  ,
				const Memory::AllocationCallbacks* _allocator   ,
				      Handle&                      _renderPass
			)
			{
				return EResult(vkCreateRenderPass(_deviceHandle, _createInfo.operator const VkRenderPassCreateInfo*(), _allocator->operator const VkAllocationCallbacks*(), &_renderPass));
			}

			/**
			 * @brief Destroy a render pass.
			 * 
			 * @details
			 * <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#vkDestroyRenderPass">Specification</a> 
			 * 
			 * \param _deviceHandle
			 * \param _renderPass
			 * \param _allocator
			 */
			static void Destroy(LogicalDevice::Handle _deviceHandle, Handle _renderPass, const Memory::AllocationCallbacks* _allocator)
			{
				vkDestroyRenderPass(_deviceHandle, _renderPass, _allocator->operator const VkAllocationCallbacks*());
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

		struct Framebuffer : public V1::Framebuffer
		{
			using Parent = V1::Framebuffer;

			struct CreateInfo : Parent::CreateInfo
			{
				CreateInfo()
				{
					SType = STypeEnum;
					Next  = nullptr  ;
				}
			};

			/**
			 * @brief Creates a framebuffer.
			 * 
			 * @details
			 * 
			 * \param _deviceHanle
			 * \param _creationSpec
			 * \param _framebuffer
			 * \return 
			 */
			static EResult Create
			(
				      LogicalDevice::Handle _deviceHanle ,
				const CreateInfo&           _creationSpec,
				      Handle&               _framebuffer
			)
			{
				return Parent::Create(_deviceHanle, _creationSpec, Memory::DefaultAllocator, _framebuffer);
			}

			using Parent::Create;

			/**
			 * @brief Destroy a framebuffer.
			 * 
			 * @details
			 * 
			 * \param _deviceHandle
			 * \param _framebuffer
			 */
			static void Destroy(LogicalDevice::Handle _deviceHandle, Handle _framebuffer)
			{
				Parent::Destroy(_deviceHandle, _framebuffer, Memory::DefaultAllocator);
			}

			using Parent::Destroy;
		};

		struct RenderPass : public V1::RenderPass
		{
			using Parent = V1::RenderPass;

			struct BeginInfo : public Parent::BeginInfo
			{
				BeginInfo()
				{
					SType = STypeEnum;
					Next  = nullptr  ;
				}
			};

			struct CreateInfo : public Parent::CreateInfo
			{
				CreateInfo()
				{
					SType = STypeEnum;
					Next = nullptr;
				}
			};

			/*struct AttachmentDescription : public Parent::AttachmentDescription
			{
			};*/

			struct SubpassDescription : public Parent::SubpassDescription
			{
				SubpassDescription()
				{
					InputAttachmentCount = 0;
					InputAttachments = nullptr;
					ColorAttachmentCount = 0;
					ColorAttachments = nullptr;
					ResolveAttachments = nullptr;
					DepthStencilAttachment = nullptr;
					PreserveAttachmentCount = 0;
					PreserveAttachments = nullptr;
				}
			};

			/**
			 * @brief Create a render pass.
			 * 
			 * @details
			 * 
			 * \param _deviceHandle
			 * \param _createInfo
			 * \param _renderPass
			 * \return 
			 */
			static EResult Create
			(
				      LogicalDevice::Handle _deviceHandle,
				const CreateInfo&           _createInfo  ,
				      Handle&               _renderPass
			)
			{
				return Parent::Create(_deviceHandle, _createInfo, Memory::DefaultAllocator, _renderPass);
			}

			using Parent::Create;

			/**
			 * @brief Destroy a render pass.
			 * 
			 * @details
			 * 
			 * \param _deviceHandle
			 * \param _renderPass
			 */
			static void Destroy(LogicalDevice::Handle _deviceHandle, Handle _renderPass)
			{
				Parent::Destroy(_deviceHandle, _renderPass, Memory::DefaultAllocator);
			}

			using Parent::Destroy;
		};

		/** @} */
	}

	namespace V3
	{
		/**
		@addtogroup Vault_3
		@{
		*/

		class Framebuffer : public V2::Framebuffer
		{
		public:
			using Parent = V2::Framebuffer;

			EResult Create(LogicalDevice::Handle _device, CreateInfo& _info)
			{
				device    = _device                 ;
				info      = _info                   ;
				allocator = Memory::DefaultAllocator;

				return Parent::Create(device, info, handle);
			}

			EResult Create(LogicalDevice::Handle _device, CreateInfo& _info, const Memory::AllocationCallbacks* _allocator)
			{
				device    = _device   ;
				info      = _info     ;
				allocator = _allocator;

				return Parent::Create(device, info, allocator, handle);
			}

			void Destroy()
			{
				Parent::Destroy(device, handle, allocator);
			}

			const Handle& GetHandle() const
			{
				return handle;
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

		protected:

			Handle handle;

			CreateInfo info;

			const Memory::AllocationCallbacks* allocator;

			LogicalDevice::Handle device;
		};

		class RenderPass : public V2::RenderPass
		{
		public:
			using Parent = V2::RenderPass;



			EResult Create(LogicalDevice::Handle _device, CreateInfo& _info)
			{
				device    = _device                 ;
				info      = _info                   ;
				allocator = Memory::DefaultAllocator;

				return Parent::Create(device, info, handle);
			}

			EResult Create(LogicalDevice::Handle _device, CreateInfo& _info, const Memory::AllocationCallbacks* _allocator)
			{
				device    = _device   ;
				info      = _info     ;
				allocator = _allocator;

				return Parent::Create(device, info, allocator, handle);
			}

			void Destroy()
			{
				Parent::Destroy(device, handle, allocator);
			}

			uint32 GetAttachmentCount()
			{
				return info.AttachmentCount;
			}

			Handle GetHandle()
			{
				return handle;
			}

			operator Handle()
			{
				return handle;
			}

			operator const Handle&() const
			{
				return handle;
			}

		protected:

			Handle handle;

			const Memory::AllocationCallbacks* allocator;

			CreateInfo info;

			LogicalDevice::Handle device;
		};

		/** @} */
	}
}
