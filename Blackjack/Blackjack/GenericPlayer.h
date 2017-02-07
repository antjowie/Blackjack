#pragma once
#include "Hand.h"

class GenericPlayer :
	public Hand
{
public:

	virtual bool IsHitting() const = 0;
	bool CheckBust() const;

	GenericPlayer(const std::string& name);

protected:
	std::string m_name;
};