/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001 Russell L. Smith.            *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the GNU Lesser General Public            *
 * License as published by the Free Software Foundation; either          *
 * version 2.1 of the License, or (at your option) any later version.    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      *
 * Lesser General Public License for more details.                       *
 *                                                                       *
 * You should have received a copy of the GNU Lesser General Public      *
 * License along with this library (see the file LICENSE.TXT); if not,   *
 * write to the Free Software Foundation, Inc., 59 Temple Place,         *
 * Suite 330, Boston, MA 02111-1307 USA.                                 *
 *                                                                       *
 *************************************************************************/

#ifndef _ODE_OBJECTS_H_
#define _ODE_OBJECTS_H_

#include "ode/common.h"
#include "ode/mass.h"

#ifdef __cplusplus
extern "C" {
#endif

/* world */

dWorldID dWorldCreate();
void dWorldDestroy (dWorldID);

void dWorldSetGravity (dWorldID, dReal x, dReal y, dReal z);
void dWorldGetGravity (dWorldID, dVector3 gravity);

void dWorldStep (dWorldID, dReal stepsize);

/* bodies */

dBodyID dBodyCreate (dWorldID);
void dBodyDestroy (dBodyID);

void  dBodySetData (dBodyID, void *data);
void *dBodyGetData (dBodyID);

void dBodySetPosition   (dBodyID, dReal x, dReal y, dReal z);
void dBodySetRotation   (dBodyID, const dMatrix3 R);
void dBodySetQuaternion (dBodyID, const dQuaternion q);
void dBodySetLinearVel  (dBodyID, dReal x, dReal y, dReal z);
void dBodySetAngularVel (dBodyID, dReal x, dReal y, dReal z);
const dReal * dBodyGetPosition   (dBodyID);
const dReal * dBodyGetRotation   (dBodyID);	/* ptr to 4x3 rot matrix */
const dReal * dBodyGetQuaternion (dBodyID);
const dReal * dBodyGetLinearVel  (dBodyID);
const dReal * dBodyGetAngularVel (dBodyID);

void dBodySetMass (dBodyID, const dMass *mass);
void dBodyGetMass (dBodyID, dMass *mass);

void dBodyAddForce            (dBodyID, dReal fx, dReal fy, dReal fz);
void dBodyAddTorque           (dBodyID, dReal fx, dReal fy, dReal fz);
void dBodyAddRelForce         (dBodyID, dReal fx, dReal fy, dReal fz);
void dBodyAddRelTorque        (dBodyID, dReal fx, dReal fy, dReal fz);
void dBodyAddForceAtPos       (dBodyID, dReal fx, dReal fy, dReal fz,
			                dReal px, dReal py, dReal pz);
void dBodyAddRelForceAtPos    (dBodyID, dReal fx, dReal fy, dReal fz,
			                dReal px, dReal py, dReal pz);
void dBodyAddRelForceAtRelPos (dBodyID, dReal fx, dReal fy, dReal fz,
			                dReal px, dReal py, dReal pz);

void dBodyGetPointPos    (dBodyID, dReal px, dReal py, dReal pz,
			  dVector3 result);
void dBodyGetPointVel    (dBodyID, dReal px, dReal py, dReal pz,
			  dVector3 result);
void dBodyGetPointRelVel (dBodyID, dReal px, dReal py, dReal pz,
			  dVector3 result);

/* joints */

dJointID dJointCreateBall (dWorldID, dJointGroupID);
dJointID dJointCreateHinge (dWorldID, dJointGroupID);
dJointID dJointCreateSlider (dWorldID, dJointGroupID);
dJointID dJointCreateContact (dWorldID, dJointGroupID, const dContact *);
dJointID dJointCreateRMotor (dWorldID, dJointGroupID);
dJointID dJointCreateHinge2 (dWorldID, dJointGroupID);

void dJointDestroy (dJointID);

dJointGroupID dJointGroupCreate (int max_size);
void dJointGroupDestroy (dJointGroupID);
void dJointGroupEmpty (dJointGroupID);

void dJointAttach (dJointID, dBodyID body1, dBodyID body2);

void dJointSetBallAnchor (dJointID, dReal x, dReal y, dReal z);
void dJointSetHingeAnchor (dJointID, dReal x, dReal y, dReal z);
void dJointSetHingeAxis (dJointID, dReal x, dReal y, dReal z);
void dJointSetHingeVel (dJointID, dReal vel);
void dJointSetHingeTmax (dJointID, dReal tmax);
void dJointSetHingeStops (dJointID, dReal low, dReal high);
void dJointSetHingeFudgeFactor (dJointID, dReal factor);
void dJointSetSliderAxis (dJointID, dReal x, dReal y, dReal z);
void dJointSetSliderVel (dJointID, dReal vel);
void dJointSetSliderFmax (dJointID, dReal fmax);
void dJointSetSliderStops (dJointID, dReal low, dReal high);
void dJointSetSliderFudgeFactor (dJointID, dReal factor);
void dJointSetRMotorAxis (dJointID, dReal x, dReal y, dReal z);
void dJointSetRMotorVel (dJointID, dReal vel);
void dJointSetRMotorTmax (dJointID, dReal tmax);
void dJointSetHinge2Anchor (dJointID, dReal x, dReal y, dReal z);
void dJointSetHinge2Axis1 (dJointID, dReal x, dReal y, dReal z);
void dJointSetHinge2Axis2 (dJointID, dReal x, dReal y, dReal z);

void dJointGetBallAnchor (dJointID, dVector3 result);
void dJointGetHingeAnchor (dJointID, dVector3 result);
void dJointGetHingeAxis (dJointID, dVector3 result);
dReal dJointGetHingeVel (dJointID);
dReal dJointGetHingeTmax (dJointID);
dReal dJointGetHingeLowStop (dJointID);
dReal dJointGetHingeHighStop (dJointID);
dReal dJointGetHingeFudgeFactor (dJointID);
dReal dJointGetHingeAngle (dJointID);
dReal dJointGetHingeAngleRate (dJointID);
dReal dJointGetSliderVel (dJointID);
dReal dJointGetSliderFmax (dJointID);
dReal dJointGetSliderLowStop (dJointID);
dReal dJointGetSliderHighStop (dJointID);
dReal dJointGetSliderFudgeFactor (dJointID);
dReal dJointGetSliderPosition (dJointID);
dReal dJointGetSliderPositionRate (dJointID);
void dJointGetSliderAxis (dJointID, dVector3 result);
void dJointGetRMotorAxis (dJointID, dVector3 result);
dReal dJointGetRMotorVel (dJointID);
dReal dJointGetRMotorTmax (dJointID);
dReal dJointGetRMotorAngle (dJointID);
dReal dJointGetRMotorAngleRate (dJointID);
void dJointGetHinge2Anchor (dJointID, dVector3 result);
void dJointGetHinge2Axis1 (dJointID, dVector3 result);
void dJointGetHinge2Axis2 (dJointID, dVector3 result);

int dAreConnected (dBodyID, dBodyID);


#ifdef __cplusplus
}
#endif

#endif
