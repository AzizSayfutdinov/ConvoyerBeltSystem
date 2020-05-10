#pragma once
class State
{
public: 
	virtual void _action() = 0;
	virtual bool _condition() = 0;
};

