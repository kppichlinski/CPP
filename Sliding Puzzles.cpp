#include "graph_state.hpp"
#include "graph_search.hpp"
#include "queue.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <random>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

template <int M, int N, typename Heuristic>
class sliding_puzzle : public graph_state
{
public:

	sliding_puzzle(const string& s, int n)
	{
		istringstream str{ s };
		for (auto& i : board)
		{
			for (auto& j : i)
			{
				int v;
				str >> v;
				j = v;
			}
		}

		shuffle(n);
	}

	template <int M, int N, typename H>
	sliding_puzzle(const sliding_puzzle<M, N, H>& s)
	{
		board = s.getBoard();
	}

	sliding_puzzle(const array<array<unsigned char, N>, M>& board) : board(board) {}

	unique_ptr<graph_state> clone() const override
	{
		return unique_ptr<graph_state>{new sliding_puzzle(*this)};
	}

	size_t hash_code() const override
	{
		size_t h = 1;

		for (auto& i : board)
		{
			for (auto& j : i)
			{
				h = 31 * h + j;
			}
		}

		return h;
	}

	vector<unique_ptr<graph_state>> get_successors() const override
	{
		vector<unique_ptr<graph_state>> r;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (board[i][j] == 0)
				{
					vector<int> possibilities;

					if (i - 1 >= 0)
					{
						possibilities.push_back(UP);
					}
					if (j + 1 < N)
					{
						possibilities.push_back(RIGHT);
					}
					if (i + 1 < M)
					{
						possibilities.push_back(DOWN);
					}
					if (j - 1 >= 0)
					{
						possibilities.push_back(LEFT);
					}

					for (auto n : possibilities)
					{
						auto state_copy = clone();
						state_copy->set_parent(this);

						switch (n)
						{
						case UP:
							dynamic_cast<sliding_puzzle&>(*state_copy).moveUp(i, j);
							break;
						case DOWN:
							dynamic_cast<sliding_puzzle&>(*state_copy).moveDown(i, j);
							break;
						case LEFT:
							dynamic_cast<sliding_puzzle&>(*state_copy).moveLeft(i, j);
							break;
						case RIGHT:
							dynamic_cast<sliding_puzzle&>(*state_copy).moveRight(i, j);
							break;
						}

						state_copy->update_score(state_copy->get_g() + 1);
						r.push_back(move(state_copy));
					}

					//cout << endl;

					return r;
				}
			}
		}

		return r;
	}

	bool is_solution() const override
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				if ((board[i][j + 1] - board[i][j] != 1))
				{
					return false;
				}
				if (i + 1 < M)
				{
					if (board[i + 1][0] - board[i][N - 1] != 1)
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	string to_string() const override
	{
		ostringstream str;

		for (auto& i : board)
		{
			for (int j : i)
			{
				str << j << " ";
			}

			str << endl;
		}

		return str.str();
	}

	static string path(const vector<const graph_state*>& path)
	{
		ostringstream s;
		int move = 1;

		for (int k = path.size() - 2; k >= 0; k--)
		{
			auto [prev_i, prev_j] = dynamic_cast<sliding_puzzle*>(const_cast<graph_state*>(path[k + 1]))->zero();
			auto [i, j] = dynamic_cast<sliding_puzzle*>(const_cast<graph_state*>(path[k]))->zero();

			s << move << ": ";
			if (i < prev_i)
			{
				s << "UP";
			}
			else if (i > prev_i)
			{
				s << "DOWN";
			}
			else if (j < prev_j)
			{
				s << "LEFT";
			}
			else
			{
				s << "RIGHT";
			}

			s << endl;

			move++;
		}

		return s.str();
	}

	const array<array<uint8_t, N>, M>& getBoard() const
	{
		return board;
	}

protected:

	bool is_equal(const graph_state& s) const override
	{
		const sliding_puzzle* st = dynamic_cast<const sliding_puzzle*>(&s);
		return st != nullptr && st->board == this->board;
	}

	double get_heuristic_grade() const override
	{
		return heuristic(this->board);
	}

	array<array<uint8_t, N>, M> board;

private:

	static constexpr Heuristic heuristic{};

	tuple<int, int> zero()
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (board[i][j] == 0)
				{
					return make_tuple(i, j);
				}
			}
		}
	}

	void moveUp(int i, int j)
	{
		swap(board[i][j], board[i - 1][j]);
	}

	void moveDown(int i, int j)
	{
		swap(board[i][j], board[i + 1][j]);
	}

	void moveLeft(int i, int j)
	{
		swap(board[i][j], board[i][j - 1]);
	}

	void moveRight(int i, int j)
	{
		swap(board[i][j], board[i][j + 1]);
	}

	void shuffle(int n)
	{
		int counter = 0;

		static random_device device;
		static default_random_engine generator(device());
		static uniform_int_distribution<int> distribution(0, 3);

		while (counter < n)
		{
			int choose = distribution(generator);

			auto [i, j] = zero();

			switch (choose)
			{
			case UP:
				if (i - 1 >= 0)
				{
					moveUp(i, j);
					counter++;
				}
				break;
			case DOWN:
				if (i + 1 < M)
				{
					moveDown(i, j);
					counter++;
				}
				break;
			case LEFT:
				if (j - 1 >= 0)
				{
					moveLeft(i, j);
					counter++;
				}
				break;
			case RIGHT:
				if (j + 1 < N)
				{
					moveRight(i, j);
					counter++;
				}
				break;
			}
		}
	}
};

template <int M, int N>
struct Manhattan
{
	double operator()(const array<array<uint8_t, N>, M>& board) const
	{
		int cnt = 0;
		int x, y;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				x = board[i][j] % N;
				y = board[i][j] / N;

				cnt += abs(y - i) + abs(x - j);
			}
		}

		return cnt;
	}
};

template <int M, int N>
struct Bad
{
	double operator()(const array<array<uint8_t, M>, N>& board) const
	{
		int cnt = 0;
		int x, y;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (board[i][j] != (i * M) + j)
				{
					cnt++;
				}
			}
		}

		return cnt;
	}
};

/*
int main()
{
	auto comp_f = [](const graph_state& a, const graph_state& b)
	{
		return a.get_f() < b.get_f();
	};

	const int M = 3;
	const int N = 3;
	int n = 500;

	string puzzle;

	for (int i = 0; i < M * N; i++)
	{
		puzzle.append(to_string(i) + " ");
	}

	sliding_puzzle<M, N, Manhattan <M, N>> s{ puzzle , n };

	informative_searcher searcher(s, comp_f);
	cout << searcher.get_stats() << endl;
	cout << searcher.get_solution(0)->to_string() << endl;
	cout << s.path(searcher.get_solution_path(0));

	return 0;
}
*/
/*
int main()
{
	auto comp_f = [](const graph_state& a, const graph_state& b)
	{
		return a.get_f() < b.get_f();
	};

	int64_t elapsed_seconds1 = 0;
	int64_t elapsed_seconds2 = 0;

	int closed1 = 0;
	int closed2 = 0;

	const int M = 3;
	const int N = 3;
	int n = 1000;

	string puzzle;

	for (int i = 0; i < M * N; i++)
	{
		puzzle.append(to_string(i) + " ");
	}

	for (int i = 0; i < 100; i++)
	{

		sliding_puzzle<M, N, Manhattan <M, N>> s{ puzzle , n };
		{
			auto start = chrono::system_clock::now();

			informative_searcher searcher(s, comp_f);
			cout << searcher.get_stats() << endl;
			cout << searcher.get_solution(0)->to_string() << endl;
			closed1 += searcher.get_closed().size();

			auto end = chrono::system_clock::now();

			elapsed_seconds1 += chrono::duration_cast<chrono::milliseconds>(end - start).count();

		}
		{
			sliding_puzzle<M, N, Bad <M, N>> S{s};

			auto start = chrono::system_clock::now();

			informative_searcher searcher(S, comp_f);
			cout << searcher.get_stats() << endl;
			cout << searcher.get_solution(0)->to_string() << endl;
			closed2 += searcher.get_closed().size();

			auto end = chrono::system_clock::now();

			elapsed_seconds2 += chrono::duration_cast<chrono::milliseconds>(end - start).count();
		}
	}

	cout << "Manhattan: " << endl;
	cout << "time: " << parse_time(elapsed_seconds1 / 100) << endl;
	cout << "closed: " << closed1 << endl;;
	cout << "Bad: " << endl;
	cout << "time: " << parse_time(elapsed_seconds2 / 100) << endl;
	cout << "closed: " << closed2 << endl;;

	return 0;
}
*/

int main()
{
	auto comp_f = [](const graph_state& a, const graph_state& b)
	{
		return a.get_f() < b.get_f();
	};

	auto comp_h = [](const graph_state& a, const graph_state& b)
	{
		return a.get_h() < b.get_h();
	};

	auto comp_equal = [](const graph_state& a, const graph_state& b)
	{
		return a.get_f() < b.get_f() || a.get_f() == b.get_f() && a.get_h() < b.get_h();
	};

	int64_t elapsed_seconds1 = 0;
	int64_t elapsed_seconds2 = 0;
	int64_t elapsed_seconds3 = 0;

	int closed1 = 0;
	int closed2 = 0;
	int closed3 = 0;

	int path_size1 = 0;
	int path_size2 = 0;
	int path_size3 = 0;

	const int M = 3;
	const int N = 3;
	int n = 1000;

	string puzzle;

	for (int i = 0; i < M * N; i++)
	{
		puzzle.append(to_string(i) + " ");
	}

	for (int i = 0; i < 100; i++)
	{
		sliding_puzzle<M, N, Manhattan <M, N>> s{ puzzle , n };

		{
			auto start = chrono::system_clock::now();

			informative_searcher searcher(s, comp_f);
			cout << searcher.get_stats() << endl;
			cout << searcher.get_solution(0)->to_string() << endl;
			closed1 += searcher.get_closed().size();
			path_size1 += searcher.get_solution_path(0).size();

			auto end = chrono::system_clock::now();

			elapsed_seconds1 += chrono::duration_cast<chrono::milliseconds>(end - start).count();
		}
		{
			auto start = chrono::system_clock::now();

			informative_searcher searcher(s, comp_h);
			cout << searcher.get_stats() << endl;
			cout << searcher.get_solution(0)->to_string() << endl;
			closed2 += searcher.get_closed().size();
			path_size2 += searcher.get_solution_path(0).size();

			auto end = chrono::system_clock::now();

			elapsed_seconds2 += chrono::duration_cast<chrono::milliseconds>(end - start).count();
		}
		{
			auto start = chrono::system_clock::now();

			informative_searcher searcher(s, comp_equal);
			cout << searcher.get_stats() << endl;
			cout << searcher.get_solution(0)->to_string() << endl;
			closed3 += searcher.get_closed().size();
			path_size3 += searcher.get_solution_path(0).size();

			auto end = chrono::system_clock::now();

			elapsed_seconds3 += chrono::duration_cast<chrono::milliseconds>(end - start).count();
		}
	}

	cout << "A*: " << endl;
	cout << "time: " << parse_time(elapsed_seconds1 / 100) << endl;
	cout << "closed: " << closed1 << endl;;
	cout << "path size: " << (path_size1 / 100) << endl << endl;

	cout << "Best-first search: " << endl;
	cout << "time: " << parse_time(elapsed_seconds2 / 100) << endl;
	cout << "closed: " << closed2 << endl;;
	cout << "path size: " << (path_size2 / 100) << endl << endl;

	cout << "With equal: " << endl;
	cout << "time: " << parse_time(elapsed_seconds3 / 100) << endl;
	cout << "closed: " << closed3 << endl;;
	cout << "path size: " << (path_size3 / 100) << endl << endl;

	return 0;
}