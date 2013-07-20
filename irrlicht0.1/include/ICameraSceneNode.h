// Copyright (C) 2002-2003 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#ifndef __I_CAMERA_SCENE_NODE_H_INCLUDED__
#define __I_CAMERA_SCENE_NODE_H_INCLUDED__

#include "ISceneNode.h"
#include "IEventReceiver.h"

namespace irr
{
namespace scene
{

	//! Defines the view frustrum. Thats the space viewed by the camera.
	/** The view frustrum is enclosed by 6 planes. These six planes share
	four points. A bounding box around these four points is also stored in
	this structure.
	*/
	struct SViewFrustrum
	{
		enum planes
		{
			//! Far plane of the frustrum. Thats the plane farest away from the eye.
			CVA_FAR_PLANE = 0,
			//! Near plane of the frustrum. Thats the plane nearest to the eye.
			CVA_NEAR_PLANE,
			//! Left plane of the frustrum.
			CVA_LEFT_PLANE,
			//! Right plane of the frustrum.
			CVA_RIGHT_PLANE,
			//! Bottom plane of the frustrum.
			CVA_BOTTOM_PLANE,
			//! Top plane of the frustrum.
			CVA_TOP_PLANE,

			//! Amount of planes enclosing the view frustum. Should be 6.
			CVA_PLANE_COUNT
		};

		core::plane3dex<f32> planes[CVA_PLANE_COUNT];
		core::vector3df rightFarDown;
		core::vector3df leftFarDown;
		core::vector3df rightFarUp;
		core::vector3df leftFarUp;

		core::aabbox3d<f32> box;
	};

	//! Scene Node which is a (controlable) camera.
	/** The whole scene will be
	rendered from the cameras point of view. Because the ICameraScenNode
	is a SceneNode, it can be attached to any other scene node, and will
	follow its parents movement, rotation and so on.
	*/
	class ICameraSceneNode : public ISceneNode, public IEventReceiver
	{
	public:

		//! Constructor
		ICameraSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id, 
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f,1.0f,1.0f))
			: ISceneNode(parent, mgr, id, position, rotation, scale) {}

		//! Destructor
		virtual ~ICameraSceneNode() {};

		//! Sets the projection matrix of the camera. The core::matrix4 class has some methods
		//! to build a projection matrix. e.g: core::matrix4::buildProjectionMatrixPerspectiveFovLH.
		//! Note that the matrix will only stay as set by this method until one of 
		//! the following Methods are called: setNearValue, setFarValue, setAspectRatio, setFOV.
		//! \param projection: The new projection matrix of the camera. 
		virtual void setProjectionMatrix(const core::matrix4& projection) = 0;

		//! Gets the current projection matrix of the camera.
		//! \return Returns the current projection matrix of the camera.
		virtual const core::matrix4& getProjectionMatrix() = 0;

		//! Gets the current view matrix of the camera.
		//! \return Returns the current view matrix of the camera.
		virtual const core::matrix4& getViewMatrix() = 0;

		//! It is possible to send mouse and key events to the camera. Most cameras
		//! may ignore this input, but camera scene nodes which are created for 
		//! example with ISceneManager::addMayaCameraSceneNode or
		//! ISceneManager::addMeshViewerCameraSceneNode, may want to get this input
		//! for changing their position, look at target or whatever. 
		virtual bool OnEvent(SEvent event) = 0;

		//! Sets the look at target of the camera
		//! \param pos: Look at target of the camera.
		virtual void setTarget(const core::vector3df& pos) = 0;

		//! Gets the current look at target of the camera
		//! \return Returns the current look at target of the camera
		virtual core::vector3df getTarget() const = 0;

		//! Sets the up vector of the camera.
		//! \param pos: New upvector of the camera.
		virtual void setUpVector(const core::vector3df& pos) = 0;

		//! Gets the up vector of the camera.
		//! \return Returns the up vector of the camera.
		virtual core::vector3df getUpVector() const = 0;

		//! \return Returns the value of the near plane of the camera.
		virtual f32 getNearValue() = 0;

		//! \return Returns the value of the far plane of the camera.
		virtual f32 getFarValue() = 0;

		//! \return Returns the aspect ratio of the camera.
		virtual f32 getAspectRatio() = 0;

		//! \return Returns the field of view of the camera.
		virtual f32 getFOV() = 0;

		//! Sets the value of the near clipping plane. (default: 1.0f)
		//! \param zn: New z near value.
		virtual void setNearValue(f32 zn) = 0;

		//! Sets the value of the far clipping plane (default: 2000.0f)
		//! \param zf: New z far value.
		virtual void setFarValue(f32 zf) = 0;

		//! Sets the aspect ratio (default: 4.0f / 3.0f)
		//! \param aspect: New aspect ratio.
		virtual void setAspectRatio(f32 aspect) = 0;

		//! Sets the field of view (Default: PI / 3.5f)
		//! \param fovy: New field of view.
		virtual void setFOV(f32 fovy) = 0;

		//! Returns the view frustrum. Needed sometimes by bspTree or LOD render nodes.
		//! \return Returns the current view frustrum.
		virtual const SViewFrustrum* getViewFrustrum() = 0;
	};

} // end namespace scene
} // end namespace irr

#endif