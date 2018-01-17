#pragma once

#pragma once
#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace type_try_emplace
{
	std::map<std::string, std::string> myMap;

	void start()
	{

		myMap.insert(make_pair("kim", "youngtae"));
		cout << myMap.find("kim")->second << endl;

		myMap.emplace("kim", "- client");
		cout << myMap.find("kim")->second << endl;



		myMap.emplace("dnf", "- client");
		cout << myMap.find("dnf")->second << endl;

		myMap.try_emplace("dnf", "hi");
		cout << myMap.find("dnf")->second << endl;


		myMap.try_emplace("dnf2", "hi");
		cout << myMap.find("dnf")->second << endl;

		myMap.clear();
		myMap.insert_or_assign("dnf", "hi");
		/*
			if( key 있으면)
				emplce_hint--> 
				이 API는 사용되지 않습니다.   unordered_set 클래스를 대신 사용하는 것이 좋습니다. 
			
			else
				insert;
		*/
	}

	// template<class _Keyty,
	// 	class... _Mappedty>
	// 	_Pairib _Try_emplace(_Keyty&& _Keyval,
	// 		_Mappedty&&... _Mapval)
	// {	// fail if _Keyval present, else emplace
	// 	iterator _Where = _Mybase::lower_bound(_Keyval);
	// 	if (_Where == _Mybase::end()
	// 		|| _DEBUG_LT_PRED(_Mybase::_Getcomp(),
	// 			_Keyval, _Mybase::_Key(_Where._Ptr)))
	// 		return (_Pairib(
	// 			_Mybase::emplace_hint(_Where,
	// 				piecewise_construct,
	// 				_STD forward_as_tuple(
	// 					_STD forward<_Keyty>(_Keyval)),
	// 				_STD forward_as_tuple(
	// 					_STD forward<_Mappedty>(_Mapval)...)),
	// 			true));	// 없으면
	// 	else
	// 		return (_Pairib(_Where, false));	// 있으면 return;
	// }


}