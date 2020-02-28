class Actor {
	public:
		// Used to track state of actor
		enum State {
			EActive,
			Epaused,
			EDead
		};
		// Constructor/distructor
		Actor(class Game* game);
		virtual ~Actor();

		// Update function called from Game (not overridable)
		void Update(float deltaTime);
		// Update all the components attached to the actor (not pverridable)
		void UpdateComponents(float deltaTime);
		// Any actor-specific update code (overridable)
		virtual void UpdateActor(float deltaTime);
		// Getters/setters
		// ...

		//Add/remove components
		void AddComponent(class Component* component);
		void RemoveComponent(class Component* component);
	private:
		// Actor's State
		State mState;
		// Transform
		Vector2 mPosition;	// Center position of actor
		float mScale;	// Uniforms scale of actor (1.0f for 100%)

		float mRotation;	// Rotation angle (in radians)
		// Components held by this actor
		std::vector<class Component*> mComponents;
		class Game* mGame;
};
