#include "game_state.hpp"
#include "game_searcher.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <random>
#include <optional>

#define HUMAN true
#define COMPUTER false

#define HUMAN_TOKEN 1
#define COMPUTER_TOKEN 2

using namespace std;

template <typename Move>
class connect4 : public game_state<typename Move>
{
public:

	connect4()
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				board[i][j] = 0;
			}
		}

		player = HUMAN;
	}

	unique_ptr<game_state<Move>> clone() const override
	{
		return unique_ptr<game_state<Move>>{new connect4(*this)};
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

	string to_string() const override
	{
		ostringstream str;

		for (auto& i : board)
		{	
			str << "---------------" << endl;

			for (int j : i)
			{
				if (j == HUMAN_TOKEN)
				{
					str << "|X";
				}
				else if (j == COMPUTER_TOKEN)
				{
					str << "|O";
				}
				else
				{
					str << "| ";
				}
			}

			str << "|" << endl;

		}

		str << "---------------" << endl;

		str << " 1 2 3 4 5 6 7" << endl;

		return str.str();
	}

	optional<double> is_terminal() const override
	{
		int human_counter = 0;
		int computer_counter = 0;
		vector<int> moves = generate_moves();

		if (moves.empty())
		{
			return 0;
		}

		//rows
		for (int i = 5; i >= 0; i--)
		{
			for (int j = 0; j < 7; j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					human_counter++;
					computer_counter = 0;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computer_counter++;
					human_counter = 0;
				}
				else if (board[i][j] == 0)
				{
					human_counter = 0;
					computer_counter = 0;
				}

				if (computer_counter >= 4)
				{
					return -numeric_limits<double>::infinity();
				}
				if (human_counter >= 4)
				{
					return numeric_limits<double>::infinity();
				}
			}

			human_counter = 0;
			computer_counter = 0;
		}	

		//columns
		for (int i = 0; i < 7; i++)
		{
			for (int j = 5; j >= 0; j--)
			{
				if (board[j][i] == HUMAN_TOKEN)
				{
					human_counter++;
					computer_counter = 0;
				}
				else if (board[j][i] == COMPUTER_TOKEN)
				{
					computer_counter++;
					human_counter = 0;
				}
				else if (board[j][i] == 0)
				{
					human_counter = 0;
					computer_counter = 0;
				}

				if (computer_counter >= 4)
				{
					return -numeric_limits<double>::infinity();
				}
				if (human_counter >= 4)
				{
					return numeric_limits<double>::infinity();
				}
			}

			human_counter = 0;
			computer_counter = 0;
		}

		//diagonally SE right side
		for (int n = 1; n < 4; n++)
		{
			for (int i = 0, j = n; j < 7; i++, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					human_counter++;
					computer_counter = 0;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computer_counter++;
					human_counter = 0;
				}
				else if (board[i][j] == 0)
				{
					human_counter = 0;
					computer_counter = 0;
				}

				if (computer_counter >= 4)
				{
					return -numeric_limits<double>::infinity();
				}
				if (human_counter >= 4)
				{
					return numeric_limits<double>::infinity();
				}
			}

			human_counter = 0;
			computer_counter = 0;
		}

		//diagonally SE left side
		for (int n = 0; n < 3; n++)
		{
			for (int i = n, j = 0; i < 6; i++, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					human_counter++;
					computer_counter = 0;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computer_counter++;
					human_counter = 0;
				}
				else if (board[i][j] == 0)
				{
					human_counter = 0;
					computer_counter = 0;
				}

				if (computer_counter >= 4)
				{
					return -numeric_limits<double>::infinity();
				}
				if (human_counter >= 4)
				{
					return numeric_limits<double>::infinity();
				}
			}

			human_counter = 0;
			computer_counter = 0;
		}

		//diagonally NE left side
		for (int n = 5; n >= 3; n--)
		{
			for (int i = n, j = 0; i >= 0; i--, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					human_counter++;
					computer_counter = 0;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computer_counter++;
					human_counter = 0;
				}
				else if (board[i][j] == 0)
				{
					human_counter = 0;
					computer_counter = 0;
				}

				if (computer_counter >= 4)
				{
					return -numeric_limits<double>::infinity();
				}
				if (human_counter >= 4)
				{
					return numeric_limits<double>::infinity();
				}
			}

			human_counter = 0;
			computer_counter = 0;
		}

		//diagonally NE right side
		for (int n = 1; n < 4; n++)
		{
			for (int i = 5, j = n; j < 7; i--, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					human_counter++;
					computer_counter = 0;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computer_counter++;
					human_counter = 0;
				}
				else if (board[i][j] == 0)
				{
					human_counter = 0;
					computer_counter = 0;
				}

				if (computer_counter >= 4)
				{
					return -numeric_limits<double>::infinity();
				}
				if (human_counter >= 4)
				{
					return numeric_limits<double>::infinity();
				}
			}

			human_counter = 0;
			computer_counter = 0;
		}

		return {};
	}

	vector<int> generate_moves() const override
	{
		vector<int> possibilities;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (board[j][i] == 0)
				{
					possibilities.push_back(i);
					break;
				}
			}
		}

		//cout << "generate_moves()" << endl;

		return possibilities;
	}

	double get_h() const override
	{
		int humanScore = 0;
		int computerScore = 0;
		int humanTokens = 0;
		int computerTokens = 0;

		//columns
		for (int i = 5; i >= 3; i--)
		{
			for (int j = 0; j < 7; j++)
			{
				for (int m = i, n = j; m >= i - 3; m--)
				{
					if (board[m][n] == HUMAN_TOKEN)
					{
						humanTokens++;
					}
					else if (board[m][n] == COMPUTER_TOKEN)
					{
						computerTokens++;
					}
				}

				if (humanTokens == 3)
				{
					humanScore++;
				}

				if (computerTokens == 3)
				{
					computerScore++;
				}

				if (humanTokens == 0 && computerTokens > 0)
				{
					computerScore += computerTokens;
				}
				else if (computerTokens == 0 && humanTokens > 0)
				{
					humanScore += humanTokens;
				}

				humanTokens = 0;
				computerTokens = 0;
			}
		}

		//rows
		for (int j = 0; j < 4; j++)
		{
			for (int i = 5; i >= 0; i--)
			{
				for (int m = i, n = j; n < j + 3; n++)
				{
					if (board[m][n] == HUMAN_TOKEN)
					{
						humanTokens++;
					}
					else if (board[m][n] == COMPUTER_TOKEN)
					{
						computerTokens++;
					}
				}

				if (humanTokens == 3)
				{
					humanScore++;
				}

				if (computerTokens == 3)
				{
					computerScore++;
				}

				if (humanTokens == 0 && computerTokens > 0)
				{
					computerScore += computerTokens;
				}
				else if (computerTokens == 0 && humanTokens > 0)
				{
					humanScore += humanTokens;
				}

				humanTokens = 0;
				computerTokens = 0;
			}
		}

		//diagonally SE right side
		for (int n = 1; n < 4; n++)
		{
			for (int i = 0, j = n; j < 7; i++, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					humanTokens++;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computerTokens++;
				}
			}

			if (humanTokens == 3)
			{
				humanScore++;
			}

			if (computerTokens == 3)
			{
				computerScore++;
			}

			if (humanTokens == 0 && computerTokens > 0)
			{
				computerScore += computerTokens;
			}
			else if (computerTokens == 0 && humanTokens > 0)
			{
				humanScore += humanTokens;
			}

			humanTokens = 0;
			computerTokens = 0;
		}

		//diagonally SE left side
		for (int n = 0; n < 3; n++)
		{
			for (int i = n, j = 0; i < 6; i++, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					humanTokens++;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computerTokens++;
				}
			}

			if (humanTokens == 3)
			{
				humanScore++;
			}

			if (computerTokens == 3)
			{
				computerScore++;
			}

			if (humanTokens == 0 && computerTokens > 0)
			{
				computerScore += computerTokens;
			}
			else if (computerTokens == 0 && humanTokens > 0)
			{
				humanScore += humanTokens;
			}

			humanTokens = 0;
			computerTokens = 0;
		}

		//diagonally NE left side
		for (int n = 5; n >= 3; n--)
		{
			for (int i = n, j = 0; i >= 0; i--, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					humanTokens++;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computerTokens++;
				}
			}

			if (humanTokens == 3)
			{
				humanScore++;
			}

			if (computerTokens == 3)
			{
				computerScore++;
			}

			if (humanTokens == 0 && computerTokens > 0)
			{
				computerScore += computerTokens;
			}
			else if (computerTokens == 0 && humanTokens > 0)
			{
				humanScore += humanTokens;
			}

			humanTokens = 0;
			computerTokens = 0;
		}

		//diagonally NE right side
		for (int n = 1; n < 4; n++)
		{
			for (int i = 5, j = n; j < 7; i--, j++)
			{
				if (board[i][j] == HUMAN_TOKEN)
				{
					humanTokens++;
				}
				else if (board[i][j] == COMPUTER_TOKEN)
				{
					computerTokens++;
				}
			}

			if (humanTokens == 3)
			{
				humanScore++;
			}

			if (computerTokens == 3)
			{
				computerScore++;
			}

			if (humanTokens == 0 && computerTokens > 0)
			{
				computerScore += computerTokens;
			}
			else if (computerTokens == 0 && humanTokens > 0)
			{
				humanScore += humanTokens;
			}

			humanTokens = 0;
			computerTokens = 0;
		}

		return (humanScore - computerScore);
	}

	unique_ptr<game_state<Move>> make_move(const Move& move) const override
	{
		auto state_copy = clone();
		int row = find_row(move);

		//cout << "row:" << row << endl;
		//cout << "column:" << move << endl;

		if (player == HUMAN)
		{
			dynamic_cast<connect4&>(*state_copy).board[row][move] = HUMAN_TOKEN;
			dynamic_cast<connect4&>(*state_copy).player = COMPUTER;
		}
		else
		{
			dynamic_cast<connect4&>(*state_copy).board[row][move] = COMPUTER_TOKEN;
			dynamic_cast<connect4&>(*state_copy).player = HUMAN;
		}

		//cout << "make_move()" << endl;

		return state_copy;
	}

	int find_row(int column) const
	{
		for (int i = 5; i >= 0; i--)
		{
			if (board[i][column] == 0)
			{
				return i;
			}
		}

		return 0;

		//cout << "find_row()" << endl;
	}

	bool getPlayer()
	{
		return player;
	}

	void setPlayer(bool p)
	{
		player = p;
	}

private:

protected:

	bool is_equal(const game_state<Move>& s) const override
	{
		const connect4* st = dynamic_cast<const connect4*>(&s);
		return st != nullptr && st->board == this->board;
	}

	bool player;
	array<array<int, 7>, 6> board;

};

int random_fun(const vector<pair<int, double>>& scores)
{
	vector<int> best_scores;

	double best = scores[0].second;

	for (auto& s : scores)
	{
		if (s.second < best)
		{
			best = s.second;
		}
	}

	cout << "best in fun: " << best << endl;

	for (auto& s : scores)
	{
		if (fabs(s.second - best) < 0.05 * fabs(best))
		{
			best_scores.push_back(s.first);
		}
	}

	random_device device;
	default_random_engine generator(device());
	uniform_int_distribution<int> distribution(0, best_scores.size()-1);

	int result = best_scores[distribution(generator)];

	return result;
}

void game()
{
	connect4<int> c4;
	alpha_beta_searcher<int> searcher(10, false);

	cout << c4.to_string() << endl;

	int column;
	bool isFull = true;
	vector<int> possibilities;

	do
	{
		possibilities = c4.generate_moves();

		if (c4.getPlayer() == HUMAN)
		{
			do
			{
				cout << "Choose column: ";
				cin >> column;
				cout << endl;

				column -= 1;

				for (auto& n : possibilities)
				{
					if (column == n)
					{
						isFull = false;
					}
				}

				if (isFull)
				{
					cout << "No space in this column !!!" << endl;
					continue;
				}

				if (column < 0 || column > 6)
				{
					cout << "Number is out of range !!!" << endl;
					continue;
				}

			} while (isFull && column < 0 || column > 6);

			cout << "Your move: " << endl;
		}
		else
		{
			searcher.do_search(c4);
			vector<pair<int, double>> scores = searcher.get_scores();
			for (auto& a : scores)
			{
				cout << "int: " << a.first << endl << "double: " << a.second << endl;
			}

			int best_index = 0;
			double best = 100;

			for (auto& s : scores)
			{
				if (s.second < best)
				{
					best = s.second;
					best_index = s.first;
				}
			}

			column = best_index;

			cout << "Computer move: " << endl;
		}

		unique_ptr<game_state<int>> new_state = c4.make_move(column);

		c4 = *dynamic_cast<connect4<int>*>(new_state.get());

		cout << c4.to_string() << endl;

		//cout << "board score: " << c4.get_h() << endl;

		optional<double> result = c4.is_terminal();

		if (result == numeric_limits<double>::infinity())
		{
			cout << "You won !!!" << endl;
			return;
		}
		else if (result == -numeric_limits<double>::infinity())
		{
			cout << "Computer won !!!" << endl;
			return;
		}
		else if (result == 0)
		{
			cout << "Draw" << endl;
		}

	} while (!possibilities.empty());
}


int main()
{
	game();

	return 0;
}