// src/subsystems/physics/physics.h
#pragma once
#include <btBulletDynamicsCommon.h>

namespace Physics
{

    class PhysicsSystem
    {
    public:
        PhysicsSystem();
        ~PhysicsSystem();

        bool Initialize();
        void Update(float deltaTime);
        void Shutdown();

        // Example method to add a rigid body
        btRigidBody *AddRigidBody(float mass, const btVector3 &position);

    private:
        bool mInitialized;
        btBroadphaseInterface *mBroadphase;
        btDefaultCollisionConfiguration *mCollisionConfig;
        btCollisionDispatcher *mDispatcher;
        btSequentialImpulseConstraintSolver *mSolver;
        btDiscreteDynamicsWorld *mDynamicsWorld;
    };

    // Global accessor
    PhysicsSystem &Get();

} // namespace Physics
