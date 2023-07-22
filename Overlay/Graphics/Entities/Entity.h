#pragma once
class Entity;
using condition = std::function< bool() >;
using child = std::shared_ptr<Entity>;
using childcontainer = std::vector< child >;

class Entity : public std::enable_shared_from_this<Entity>
{

protected:
	bool Visible;
	bool Blocked = false;

	condition Condition;

	child Parent;
	child ChildRelativeParent;

	Vector2 Pos;
	Vector2 Size;
	Vector2 OriginalSize;
	Vector2 Scale;
	Vector2 TextSize;
	Vector2 ParentPos;
	Vector2 ParentSize;

	std::wstring Name;

	Entity* Instance = this;

	float LastClick = 0;
public:
	// This can be overriden by the parent.
	virtual void Draw() {};
	virtual void Update() {};

	virtual childcontainer& GetContainer() { static childcontainer bad{}; return bad; }
	virtual size_t Children() { return 0; }

	virtual Vector2 GetPos() { return Pos; }
	virtual Vector2 GetSize() { return Size; }
	virtual Vector2 GetScale() { return Scale; }



	child GetChildRelativeParent();
	child GetParent();
	Entity* GetInstance();

	bool IsVisible();

	float GetLastClick();

	void SetLastClick(float value);
	void SetCondition(condition condition);
	void SetVisible(bool visible);
	void SetBlocked(bool block);
	void SetBlockedSiblings(bool block);
	void SetParent(child parent);
	void SetRelativeParent(child parent);

	friend class Container;
	friend class Tab;

};
class Container : public Entity
{
protected:
	childcontainer ContainerInstance;
public:
	virtual child Push(child child)
	{

		child.get()->Parent = shared_from_this();
		ContainerInstance.emplace_back(child);
		return child;

	}
	void Draw();
	void Update();
	virtual childcontainer& GetContainer() override { return ContainerInstance; }
	virtual size_t Children() override { return ContainerInstance.size(); }


};
using EntityVector = std::shared_ptr< Container >;