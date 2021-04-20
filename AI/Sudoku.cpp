#include "graph_state.hpp"
#include "graph_search.hpp"
#include "queue.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

template<int M, int N>
class generic_sudoku : public graph_state
{
public:

	generic_sudoku(const string& s)
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
	}

	generic_sudoku(const array<array<unsigned char, M* N>, M* N>& board) : board(board) {}

	unique_ptr<graph_state> clone() const override
	{
		return unique_ptr<graph_state>{new generic_sudoku(*this)};
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

		for (int i = 0; i < M * N; i++)
		{
			for (int j = 0; j < M * N; j++)
			{
				if (board[i][j] == 0)
				{
					vector<uint8_t> possibilities;
					vector<int> to_delete;
					vector<int> result(M * N);

					for (int k = 1; k <= M * N; k++)
					{
						possibilities.push_back(k);
					}

					const int left = (j / N) * N;
					const int top = (i / M) * M;

					for (int n = top; n < top + M; n++)
					{
						for (int m = left; m < left + N; m++)
						{
							if (board[n][m] != 0)
							{
								to_delete.push_back(board[n][m]);
							}
						}
					}

					for (int n = 0; n < M * N; n++)
					{
						if (board[i][n] != 0)
						{
							to_delete.push_back(board[i][n]);
						}
					}

					for (int n = 0; n < M * N; n++)
					{
						if (board[n][j] != 0)
						{
							to_delete.push_back(board[n][j]);
						}
					}

					sort(to_delete.begin(), to_delete.end());
					to_delete.erase(unique(to_delete.begin(), to_delete.end()), to_delete.end());
					result.erase(set_difference(possibilities.begin(), possibilities.end(), to_delete.begin(), to_delete.end(), result.begin()), result.end());

					//cout << i << ", " << j << ": ";

					for (auto n : result)
					{
						//cout << static_cast<int>(n) << " ";
						auto state_copy = clone();
						dynamic_cast<generic_sudoku&>(*state_copy).board[i][j] = n;
						state_copy->update_score(get_g() + 1);
						state_copy->set_parent(this);
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
		for (auto& i : board)
		{
			for (auto& j : i)
			{
				if (j == 0)
				{
					return false;
				}
			}
		}
		return true;
	}

	string to_string() const override
	{
		ostringstream str;
		int counter_vertically = M - 1;
		int additional = 0;
		int strpis = 0;
		string strip = "-";

		for (int i = 0; i < 4 * M; i++)
		{
			strip += "-";
		}

		str << strip << endl;

		for (auto& i : board)
		{
			for (int j : i)
			{
				counter_vertically++;
				additional++;

				if (counter_vertically == M)
				{
					str << "|";
					counter_vertically = 0;
				}

				if (j == 0)
				{
					str << '.';
				}
				else
				{
					str << j;
				}

				if (additional == M * N)
				{
					str << "|";
					additional = 0;
				}
			}

			strpis++;

			if (strpis == M)
			{
				str << endl << strip;
				strpis = 0;
			}

			str << endl;
		}
		return str.str();
	}

protected:

	bool is_equal(const graph_state& s) const override
	{
		const generic_sudoku* st = dynamic_cast<const generic_sudoku*>(&s);
		return st != nullptr && st->board == this->board;
	}

	array<array<uint8_t, M* N>, M* N> board;

};

template <int M, int N, typename Heuristic>
class sudoku_state : public generic_sudoku<M, N>
{
public:

	sudoku_state(const string& s) : generic_sudoku<M, N>(s) {}

	unique_ptr<graph_state> clone() const override
	{
		return unique_ptr<graph_state>{new sudoku_state{ *this }};
	}

protected:

	double get_heuristic_grade() const override
	{
		return heuristic(this->board);
	}

private:

	static constexpr Heuristic heuristic{};
};

template <int M, int N>
struct H_remaining
{
	double operator()(const array<array<uint8_t, M* N>, M* N>& board) const
	{
		int cnt = 0;

		for (const auto& i : board)
		{
			for (const auto& j : i)
			{
				if (j == 0)
				{
					cnt++;
				}
			}
		}

		return cnt;
	}
};

template <int M, int N>
struct H_sum
{
	double operator()(const array<array<uint8_t, M* N>, M* N>& board) const
	{
		int cnt = 0;

		for (int i = 0; i < M * N; i++)
		{
			for (int j = 0; j < M * N; j++)
			{
				if (board[i][j] == 0)
				{
					vector<uint8_t> possibilities;
					vector<int> to_delete;
					vector<int> result(M * N);

					for (int k = 1; k <= M * N; k++)
					{
						possibilities.push_back(k);
					}

					const int left = (j / N) * N;
					const int top = (i / M) * M;

					for (int n = top; n < top + M; n++)
					{
						for (int m = left; m < left + N; m++)
						{
							if (board[n][m] != 0)
							{
								to_delete.push_back(board[n][m]);
							}
						}
					}

					for (int n = 0; n < M * N; n++)
					{
						if (board[i][n] != 0)
						{
							to_delete.push_back(board[i][n]);
						}
					}

					for (int n = 0; n < M * N; n++)
					{
						if (board[n][j] != 0)
						{
							to_delete.push_back(board[n][j]);
						}
					}

					sort(to_delete.begin(), to_delete.end());
					to_delete.erase(unique(to_delete.begin(), to_delete.end()), to_delete.end());
					result.erase(set_difference(possibilities.begin(), possibilities.end(), to_delete.begin(), to_delete.end(), result.begin()), result.end());

					cnt += result.size();
				}
			}
		}

		return cnt;
	}
};

template<int M, int N, typename Heuristic>
class sudoku_minimal : public sudoku_state<M, N, Heuristic>
{
public:

	sudoku_minimal(const string& s) : sudoku_state<M, N, Heuristic>(s) {}

	unique_ptr<graph_state> clone() const override
	{
		return unique_ptr<graph_state>{new sudoku_minimal{ *this }};
	}

	vector<unique_ptr<graph_state>> get_successors() const override
	{
		vector<unique_ptr<graph_state>> r;

		int x, y;
		vector<int> solutions(M * N + 1);

		for (int i = 0; i < M * N; i++)
		{
			for (int j = 0; j < M * N; j++)
			{
				if (generic_sudoku<M, N>::board[i][j] == 0)
				{
					vector<uint8_t> possibilities;
					vector<int> to_delete;
					vector<int> result(M * N);

					for (int k = 1; k <= M * N; k++)
					{
						possibilities.push_back(k);
					}

					const int left = (j / N) * N;
					const int top = (i / M) * M;

					for (int n = top; n < top + M; n++)
					{
						for (int m = left; m < left + N; m++)
						{
							if (generic_sudoku<M, N>::board[n][m] != 0)
							{
								to_delete.push_back(generic_sudoku<M, N>::board[n][m]);
							}
						}
					}

					for (int n = 0; n < M * N; n++)
					{
						if (generic_sudoku<M, N>::board[i][n] != 0)
						{
							to_delete.push_back(generic_sudoku<M, N>::board[i][n]);
						}
					}

					for (int n = 0; n < M * N; n++)
					{
						if (generic_sudoku<M, N>::board[n][j] != 0)
						{
							to_delete.push_back(generic_sudoku<M, N>::board[n][j]);
						}
					}

					sort(to_delete.begin(), to_delete.end());
					to_delete.erase(unique(to_delete.begin(), to_delete.end()), to_delete.end());
					result.erase(set_difference(possibilities.begin(), possibilities.end(), to_delete.begin(), to_delete.end(), result.begin()), result.end());

					if (result.size() < solutions.size())
					{
						x = i;
						y = j;
						solutions = result;
					}

					if (solutions.size() == 1)
					{
						auto state_copy = clone();
						dynamic_cast<sudoku_minimal&>(*state_copy).board[x][y] = solutions[0];
						state_copy->update_score(state_copy->get_g() + 1);
						state_copy->set_parent(this);
						r.push_back(move(state_copy));
						return r;
					}
				}
			}
		}

		for (auto n : solutions)
		{
			auto state_copy = clone();
			dynamic_cast<sudoku_minimal&>(*state_copy).board[x][y] = n;
			state_copy->update_score(state_copy->get_g() + 1);
			state_copy->set_parent(this);
			r.push_back(move(state_copy));
		}

		return r;
	}

};

int silnia(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return n * silnia(n - 1);
	}
}

int main()
{


	int64_t elapsed_seconds1;

	int64_t elapsed_seconds2;

	auto comp = [](const graph_state& a, const graph_state& b)
	{
		return a.get_h() < b.get_h();
	};

	string line;

	int counter = 0;

	ifstream stream("C:\\Users\\kppic\\source\\repos\\Sudoku\\Release\\sudoku");

	while (getline(stream, line))
	{
		cout << line << endl;

		cout << counter++ << endl;

		auto start = chrono::system_clock::now();
		{
			sudoku_state<3, 3, H_remaining<3, 3>> s{ line };

			informative_searcher searcher(s, comp);
			cout << searcher.get_stats() << endl;
			cout << searcher.get_solution(0)->to_string() << endl;

		}
		auto end = chrono::system_clock::now();

		elapsed_seconds1 += chrono::duration_cast<chrono::milliseconds>(end - start).count();

		start = chrono::system_clock::now();
		{
			sudoku_state<3, 3, H_sum<3, 3>> s{ line };

			informative_searcher searcher(s, comp);
			cout << searcher.get_stats() << endl;
			cout << searcher.get_solution(0)->to_string() << endl;

		}
		end = chrono::system_clock::now();

		elapsed_seconds2 += chrono::duration_cast<chrono::milliseconds>(end - start).count();

		
	}

	cout << endl;
	cout << "H_remaining time: " << elapsed_seconds1;
	cout << endl;
	cout << "H_sum time: " << elapsed_seconds2;

	/*
	{
		sudoku_state<2, 3, H_remaining<2, 3>> s{
			"1 2 3 4 5 6 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0" };

		informative_searcher searcher(s, comp, numeric_limits<size_t>::max());
		cout << searcher.get_stats() << endl;
		cout << searcher.get_solution(0)->to_string() << endl;

		size_t solutions = searcher.get_number_of_solutions();
		cout << "Full number of solutions: " << silnia(6) * solutions;
	}

	{
		sudoku_minimal<2, 3, H_remaining<2, 3>> s{
			"1 2 3 4 5 6 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0 \
		0 0 0 0 0 0" };

		informative_searcher searcher(s, comp, numeric_limits<size_t>::max());
		cout << searcher.get_stats() << endl;
		cout << searcher.get_solution(0)->to_string() << endl;

		size_t solutions = searcher.get_number_of_solutions();
		cout << "Full number of solutions: " << silnia(6) * solutions;
	}
	*/

	return 0;
}
