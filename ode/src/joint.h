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

#ifndef _ODE_JOINT_H_
#define _ODE_JOINT_H_


#include "objects.h"
#include "ode/contact.h"
#include "stack.h"


// joint flags
enum {
  // if this flag is set, the joint was allocated in a joint group
  dJOINT_INGROUP = 1,

  // if this flag is set, the joint was attached with arguments (0,body).
  // our convention is to treat all attaches as (body,0), i.e. so node[0].body
  // is always nonzero, so this flag records the fact that the arguments were
  // swapped.
  dJOINT_REVERSE = 2
};


// there are two of these nodes in the joint, one for each connection to a
// body. these are node of a linked list kept by each body of it's connecting
// joints. but note that the body pointer in each node points to the body that
// makes use of the *other* node, not this node. this trick makes it a bit
// easier to traverse the body/joint graph.

struct dJointNode {
  dJoint *joint;		// pointer to enclosing dJoint object
  dBody *body;			// *other* body this joint is connected to
  dJointNode *next;		// next node in body's list of connected joints
};


struct dJoint : public dObject {
  // naming convention: the "first" body this is connected to is node[0].body,
  // and the "second" body is node[1].body. if this joint is only connected
  // to one body then the second body is 0.

  // info returned by getInfo1 function. the constraint dimension is nub+nlcp,
  // i.e. that is the total number of rows in the jacobian. `nub' is the
  // number of unbounded variables at the start, and `nlcp' is the number of
  // variables subject to LCP constraints (which appear after the `nub'
  // variables). nub+nlcp must be <= 6.

  struct Info1 {
    int nub;
    int nlcp;
  };

  // info returned by getInfo2 function

  struct Info2 {
    // integrator parameters: frames per second (1/stepsize), error reduction
    // parameter (0..1).
    dReal fps,erp;

    // for the first and second body, and for the unbounded and LCP variables,
    // pointers to two (linear and angular) n*3 jacobian sub matrices, stored
    // by rows. these matrices will have been initialized to 0 on entry.
    // if the second body is zero then the J2xx pointers may be 0.
    dReal *J1lu,*J1au,*J2lu,*J2au;	// unbounded variables
    dReal *J1ll,*J1al,*J2ll,*J2al;	// LCP variables

    // elements to jump from one row to the next in J's
    int rowskip;

    // right hand side of the equation J*a = c (unbounded,LCP). this vector
    // will be set to zero on entry.
    dReal *cu,*cl;
  };

  // virtual function table: size of the joint structure, function pointers.
  // we do it this way instead of using C++ virtual functions because
  // sometimes we need to allocate joints ourself within a memory pool.

  typedef void init_fn (dJoint *joint);
  typedef void getInfo1_fn (dJoint *joint, Info1 *info);
  typedef void getInfo2_fn (dJoint *joint, Info2 *info);
  typedef void setAnchor_fn (dJoint *joint, dReal x, dReal y, dReal z);
  typedef void setAxis_fn (dJoint *joint, dReal x, dReal y, dReal z);
  typedef void getAnchor_fn (dJoint *joint, dVector3 result);
  typedef void getAxis_fn (dJoint *joint, dVector3 result);
  struct Vtable {
    int size;
    init_fn *init;
    getInfo1_fn *getInfo1;
    getInfo2_fn *getInfo2;
    setAnchor_fn *setAnchor;
    setAxis_fn *setAxis;
    getAnchor_fn *getAnchor;
    getAxis_fn *getAxis;
  };

  Vtable *vtable;		// virtual function table
  int flags;			// dJOINT_xxx flags
  dJointNode node[2];		// connections to bodies. node[1].body can be 0
};


struct dJointGroup {
  int num;		// number of joints on the stack
  dJoint *firstjoint;	// address of first joint on the stack
  dStack stack;		// a stack of (possibly differently sized) dJoint
};			// objects.


// ball and socket

struct dJointBall : public dJoint {
  dVector3 anchor1;		// anchor w.r.t first body
  dVector3 anchor2;		// anchor w.r.t second body
};
extern struct dJoint::Vtable dball_vtable;


// hinge

struct dJointHinge : public dJoint {
  dVector3 anchor1;		// anchor w.r.t first body
  dVector3 anchor2;		// anchor w.r.t second body
  dVector3 axis1;		// axis w.r.t first body
  dVector3 axis2;		// axis w.r.t second body
};
extern struct dJoint::Vtable dhinge_vtable;


// slider. if body2 is 0 then qrel is the absolute rotation of body1 and
// offset is the position of body1 center along axis1.

struct dJointSlider : public dJoint {
  dVector3 axis1;		// axis w.r.t first body
  dQuaternion qrel;		// relative rotation body1 -> body2
  dVector3 offset;		// point relative to body2 that should be
};				// aligned with body1 center along axis1
extern struct dJoint::Vtable dslider_vtable;


// contact

struct dJointContact : public dJoint {
  dContact contact;
};
extern struct dJoint::Vtable dcontact_vtable;



#endif
