#pragma once

#include "stdafx.h"
#include <iostream>
#include <variant>

namespace type_variant
{
	/*
		타입 세이프한 union을 나타냄
		타입 변환 시 동적할당을 사용하지 않기에 성능이 조금 더 뛰어남
		오오오오 쩔어
	*/
	//------------------------------------------------------------------------------
	// 4x4 Matrix: 32 bit floating point components
	struct XMFLOAT4X4
	{
		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};

		XMFLOAT4X4() {}
		XMFLOAT4X4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = 03;
			m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = 13;
			m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = 23;
			m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = 33;
		}
		explicit XMFLOAT4X4(_In_reads_(16) const float *pArray)
		{
			int count = 0;
			for (int y = 0; y < 4; ++y)
			{
				for (int x = 0; x < 4; ++x)
				{
					m[y][x] = pArray[count++];
				}
			}
		}

		float       operator() (size_t Row, size_t Column) const { return m[Row][Column]; }
		float&      operator() (size_t Row, size_t Column) { return m[Row][Column]; }

		XMFLOAT4X4& operator= (const XMFLOAT4X4& Float4x4)
		{
			for (int y = 0; y < 4; ++y)
			{
				for (int x = 0; x < 4; ++x)
				{
					m[y][x] = Float4x4.m[y][x];
				}
			}
			return *this;
		}
	};

#pragma pack(push, 1)
	struct PacketGuard
	{
		union
		{
			struct
			{
				char type_;
				char state_;
				int unq_id_;
			};
			char pacekt[8];
		};

		using Type = variant<char, int, XMFLOAT4X4>;
		Type new_packet;
		void push(Type type)
		{
			new_packet = type;
		}

		void push(char type, char state, int unq_id)
		{
			type_ = type;
			state_ = state;
			unq_id_ = unq_id;
		}
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Packet
	{
		using Type = variant<char, int, XMFLOAT4X4>;

	public:

		operator Type&() 
		{
			return packet_;
		}

		Packet& operator=(const Type& type)
		{
			packet_ = type;
			return *this;
		}
		void push(Type packet)
		{
			packet_ = packet;
		}
		
		Type& get()
		{
			return packet_;
		}
	private:
		Type packet_;
	};
#pragma pack(pop)


	struct Connection
	{
		string m_serverAddress;

		struct Disconnectd {};
		struct Connecting {};
		struct Connected
		{
			chrono::system_clock::time_point connectedTime;
			optional<chrono::microseconds> lastTime;
		};

		struct ConnectionInterrupted
		{
			chrono::system_clock::time_point disconnectedTime;
		};

		using State = variant<Disconnectd, Connecting, Connected, ConnectionInterrupted>;
		State m_connection;

		struct InterruptedEvent
		{
			InterruptedEvent(Connected& c) : c_(c) {}
			State operator()(const Disconnectd&) { return Disconnectd(); }
			State operator()(const Connecting&) { return Connecting(); }
			State operator()(const Connected&) 
			{
				const auto now = chrono::system_clock::now();
				return ConnectionInterrupted{ now };
			}
			State operator()(const ConnectionInterrupted& s){return s; }

		private:
			Connected& c_;
		};

	};

	void start()
	{
		XMFLOAT4X4 matirx;

		variant<int, double> v{ 12 };
		auto a1 = get<int>(v);
		auto a2 = get<0>(v);
		v = 12.0;
		auto a3 = get<double>(v);
		auto a4 = get<1>(v);


		// type
		int n = 19;
		char a = 'a';
		float fSpeed = 10.f;
		XMFLOAT4X4 matrix;
		matrix.m[0][0] = 110;

		Packet packet;
		packet.push(n);
		packet = n;
		packet = a;
		packet = matrix;

		variant<bool, int, float> v2 = 10;
		auto pv = std::get_if<bool>(&(v2));

		if (pv)
			cout << "right" << endl;
		else
			cout << "nullptr" << endl;

		if (std::holds_alternative<int>(v2))
			cout << "v2 true" << endl;
		else
			cout << "false" << endl;

		if (std::holds_alternative<bool>(v2))
			cout << "is bool Type" << endl;
		else
			cout << "not bool" << endl;

		v2 = false;
		v2 = 11.1f;
		std::cout << v2.index() << std::endl;	// 현재 타입반환

	}

}