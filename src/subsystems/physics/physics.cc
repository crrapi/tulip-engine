// src/subsystems/physics/physics.cc
#include "physics.h"
#include "src/core/logging.h"

namespace Physics
{

    static PhysicsSystem gPhysicsSystem;

    PhysicsSystem::PhysicsSystem()
        : mInitialized(false),
          mBroadphase(nullptr),
          mCollisionConfig(nullptr),
          mDispatcher(nullptr),
          mSolver(nullptr),
          mDynamicsWorld(nullptr)
    {
    }

    PhysicsSystem::~PhysicsSystem()
    {
        if (mInitialized)
        {
            Shutdown();
        }
    }

    bool PhysicsSystem::Initialize()
    {
        Core::Logging::Log("[Physics] Initializing Bullet Physics...");

        // Initialize Bullet components
        mCollisionConfig = new btDefaultCollisionConfiguration();
        mDispatcher = new btCollisionDispatcher(mCollisionConfig);
        mBroadphase = new btDbvtBroadphase();
        mSolver = new btSequentialImpulseConstraintSolver();
        mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfig);
        mDynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

        mInitialized = true;
        Core::Logging::Log("[Physics] Bullet Physics initialized successfully.");
        return true;
    }

    void PhysicsSystem::Update(float deltaTime)
    {
        if (!mInitialized || !mDynamicsWorld)
            return;

        mDynamicsWorld->stepSimulation(deltaTime, 10); // maxSubSteps = 10
        Core::Logging::Log("[Physics] Bullet Physics simulation step.");
    }

    void PhysicsSystem::Shutdown()
    {
        Core::Logging::Log("[Physics] Shutting down Bullet Physics...");

        delete mDynamicsWorld;
        delete mSolver;
        delete mBroadphase;
        delete mDispatcher;
        delete mCollisionConfig;

        mDynamicsWorld = nullptr;
        mSolver = nullptr;
        mBroadphase = nullptr;
        mDispatcher = nullptr;
        mCollisionConfig = nullptr;

        mInitialized = false;
        Core::Logging::Log("[Physics] Bullet Physics shutdown complete.");
    }

    btRigidBody *PhysicsSystem::AddRigidBody(float mass, const btVector3 &position)
    {
        if (!mInitialized || !mDynamicsWorld)
            return nullptr;

        // Create collision shape
        btCollisionShape *shape = new btSphereShape(1.0f); // Example: sphere with radius 1.0

        // Create motion state
        btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));

        // Calculate inertia
        btVector3 inertia(0, 0, 0);
        if (mass != 0.0f)
            shape->calculateLocalInertia(mass, inertia);

        // Create rigid body
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
        btRigidBody *body = new btRigidBody(rbInfo);

        // Add to dynamics world
        mDynamicsWorld->addRigidBody(body);

        Core::Logging::Log("[Physics] Added a rigid body to the dynamics world.");
        return body;
    }

    PhysicsSystem &Get()
    {
        return gPhysicsSystem;
    }

} // namespace Physics
