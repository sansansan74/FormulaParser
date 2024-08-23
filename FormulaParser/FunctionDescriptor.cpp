#include "FunctionDescriptor.h"

string FunctionDescriptor::CheckParamCount(const string& functionName, int paramCount) const {
	// if all normal - return ""
	// if error - return error message
	if (this->paramCount < 0)
	{
		if (paramCount == 0)
			return "must have >0 parameters";

		return "";
	}

	if (this->paramCount != paramCount)
	{
		return "must have " + to_string(this->paramCount) + " params";
	}

	return "";		// all normal
}

