#pragma once

namespace C17
{
	namespace Template
	{
		// template<typename ...Args>
		// std::ostream& operator << (std::ostream& os, Args&&.. args)
		// {
		// 	os << args;
		// 	return os;
		// }

		// template <typename ...Args>
		// void print(Args&&...args)
		// {
		// 	(std::cout << ... << std::forward<Args>(args)) << std::endl;
		// }

		template <typename... Args>
		int sum(Args... args)
		{
			return (... + args);
		}

		void start();
	}

	namespace Auto_Deduction
	{
		void start();
	}

	namespace Constexpr_lambdas
	{
		// C++11�� ��� ǥ���� (constexpr const expression)
		// ���� ������ �� �ִ� ��Ÿ ���α׷���
		// ������ ���̳� �Լ��� ������ ������ Ÿ�ӿ� ó��
		// �Լ� �������� �ϳ��� ǥ���ĸ� ����� �� �ְ�, �ݵ�� ���ͷ��� ��ȯ�ؾ� ������
		// C++14������ ������ ���ϵǾ���

		constexpr int n = 0; // ok
		// constexpr int m = time(NULL); //error C2127

		constexpr int square(const int& x)
		{
			return (x * x);
		}

		int lambda(const int& a, const int& b);

		void factorial(const int& n);

		void start();

		void start_capture();

		struct MyObj
		{
			int value{ 123 };

			auto getValueCopy();

			auto getValueRef();
		};

	}

	namespace Attribute
	{
		/*
		 C++ 14
			 [noreturn]	: �� �Լ��� �������� ����
			 [carries_depnedency] : ���Ӽ� ü���� �Լ� �������� ���ĵ� (?)
			 [deprecated] : ����� �� ������, �������� ����( ��� X)
		C++17
			[fallthrough] : switch-case ������ ���, �Ϸ���� ������ ��Ÿ��(?)
			[nodiscard] : �Լ��� ���ϰ��� �ִµ� ������ ��� ����� ǥ��
			[maybe_unused] : ������� �ʴ� ������ ���� ����� ǥ������ ����
		*/

		[[noreturn]] void func();
		[[noreturn]] void noFunc(int i);


		// nodiscard
		struct[[nodiscard]] Object
		{
			int id_;
		};
		Object factory_create(int n);
		void start_nodiscard();

		// maybe_unused
		static void no_use([[maybe_unused]] int a, int b);
		static void no_use(int a);
		static void start_maybe_nouse();
	}

	namespace ClassTemplate
	{
		struct Object
		{
			static inline std::string const name = "dnf";
		};

	}

	namespace Memo_init
	{
		class Monster
		{
			int state;

			public:
				const int getState() const;

				void addState();

				void update();

				Monster();
		};
	}

	namespace initalize
	{	
		static int gId = 0;

		struct QuestScript
		{
			int	   id_;
			int	   next_;
			std::string name;
			QuestScript(const int id = -1) : id_(id)
			{
				next_ = ++gId;
			}
			QuestScript() : id_(rand()%10000)
			{
				next_ = ++gId;
			}
		};	
		
		class QuestManager
		{
			using QuestPtr = std::shared_ptr<QuestScript>;
			using QuestData = pair<int, QuestPtr>;
			using QusetMap = map<int, QuestPtr>;

			QusetMap questMap;
			QuestPtr curScript;

		public:

			QuestManager()
			{
				clear();
				create();
			}

			void create()
			{
				default_random_engine dre;
				uniform_int_distribution<int> uid(0, 100);

				questMap.insert(QuestData(-1, std::make_shared<QuestScript>(-1)));

				for (int i = 0; i < 10; ++i)
					questMap.insert(QuestData(i, std::make_shared<QuestScript>(i)));

				curScript = questMap[-1];

			}
			void clear()
			{
				questMap.clear();
			}

			void nextQuest(const int curIndex)
			{
				if (QuestData data = *(questMap.find(curIndex)); data.second == curScript)
				{
					curScript = questMap[curScript->next_];
				}
				
				switch (QuestData data = *(questMap.find(curIndex)); data.first)
				{
					case 0:
						std::cout << data.second->id_ << std::endl;
						break;
					case 1:
						std::cout << data.second->id_ << std::endl;
						break;
					default:
						cout << "default : " << data.second->id_ << endl;
						break;
				}
			}
			void show()
			{
				nextQuest(-1);
				nextQuest(curScript->id_);
				nextQuest(curScript->id_);
				nextQuest(curScript->id_);
			}
		};

		void start();
		
	}

	namespace Ư�����������
	{
		/// Ư�� ��ϸ� ������ ����
		template <typename T>
		constexpr bool isIntegral()
		{
			if constexpr (std::is_integral<T>::value)
				return true;
			return false;
		}

		static_assert(isIntegral<int>() == true);
		static_assert(isIntegral<char>() == true);
	}

	namespace type_any
	{
		/*
			boost.any ��� ���̺귯��
			��� ������ ������ ���� (��, ��������ڸ� �����ؾ� ��)
			any_cast()�� ���� ���ϴ� Ÿ������ ��ȯ�� ����� ���� �� ����
		*/
		class Monster
		{
		public:
			int k;

			Monster()
			{
				k = rand();
			}
			Monster(int k_)
			{
				k = k_;
			}

			Monster(const Monster& mon)
			{
				k = mon.k;
			}

			Monster& operator=(Monster& mon)
			{
				k = mon.k;
			}

			Monster& operator=(Monster&& mon)
			{
				k = mon.k;
			}
		};

		struct Name
		{
			std::string name;

			Name& operator=(Name mon)
			{
				name = mon.name;
			}
		};

		class AnyManager
		{
			std::vector<any> v;

			template<class T>
			bool isVaild(const int n)
			{
				if (v.size() < n)
					return false;

				try {
					std::any_cast<T>(v[n]);
					cout << "true" << endl;
					return true;
				}
				catch (const std::bad_any_cast& e) {
					std::cout << e.what() << endl;
					return false;
				}
			}

		public:
			void push(std::any in);

			void valid()
			{
				while (1)
				{
					int t, n;
					switch (cin >> t >> n; t)
					{
					case 0:
						isVaild<int>(n);
						break;

					case 1:
						isVaild<char>(n);
						break;

					case 2:
						isVaild<Name>(n);
						break;

					case 3:
						isVaild<Monster>(n);
						break;
					}
				}
			}
		};

		void start();
	}

};
#pragma region [fold express]
/*

	template<typename ...Args>
	int sum(Args&&... args)
	{
	return (args + ... + 0); // Binary right
	}//		   (E  op ... op I)

	template<typename ...Args>
	int sum2(Args&&... args)
	{
	return (0 + ... + args);	// Binary left
	}	//     (I op ... op Express)

	template<typename ...Args>
	bool isOk(Args&&... args) // unary left fold expands
	{
	return ( ... && args); // OK
	}//		   ( ...  op  E)
	template<typename ...Args>
	bool isFalse(Args&&... args) // unary right fold expands
	{
	return (args && ...); // OK
	}//		   ( E  op  ...)
*/
#pragma endregion