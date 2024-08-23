#include "FunctionDescriptor.h"

string FunctionDescriptor::CheckParamCount(const string& name, int paramCount) const {
	if (this->paramCount < 0)
	{
		if (paramCount == 0)
			return "must have >0 parameters";
	}
	else
	{
		if (this->paramCount != paramCount)
		{
			return "must have " + to_string(this->paramCount) + " params";
		}
	}

	return "";
}

