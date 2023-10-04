/*
перебираем индексы в таблице по порядку
(инкрементим сначала j, а потом i, т.к. это более cache-friendly)
если клетка заполнена, идём дальше
если пустая, то перебираем числа для заполнения.
за O(1) проверяем, нарушатся ли инварианты, если в клетке [i][j]
поставить новое число. 

если дошли до конца таблицы, значит все инварианты до этого не нарушены
и все клетки заполнены. значит нашли ответ.

двумерные массивы, которые хранят, какие числа уже использованы в 
строке/столбце/клетке_3x3, храним как одномерные, чтобы уменьшить
число разыменований. а ещё это cache-friendly, т.к. в recursionSolve
в цикле мы всё сразу загрузим в cache

используем vector<char> вместо vector<bool>, чтобы обменять память на
время.

board решли передавать в качестве параметра, т.к. если поле засунуть,
то понятнее не станет.
*/
class Solution {
    // придерживаюсь того же codestyle, что и у названия исходного метода
    static size_t getCellIndex(size_t i, size_t j) {
        static constexpr size_t kCellSize = 3;
        static constexpr size_t kCellsCount = kBoardSize / kCellSize;
        return (i / kCellSize) * kCellsCount + j / kCellSize;
    }
    bool recursionSolve(vector<vector<char>>& board, size_t i, size_t j) {
        while (i < board.size() && board[i][j] != '.') {
            ++j;
            if (j == board.size()) {
                j = 0;
                ++i;
            }
        }
        if (i == board.size()) {
            return true;
        }
        size_t cell_index = getCellIndex(i, j);
        for (size_t number = 1; number <= board.size(); ++number) {
            if (rows_occurencies_[i * kDigitsCount + number] || 
                columns_occurencies_[j * kDigitsCount + number] ||
                cells_occurencies_[cell_index * kDigitsCount + number]) {
                continue;
            }
            rows_occurencies_[i * kDigitsCount + number] = 
            columns_occurencies_[j * kDigitsCount + number] =
            cells_occurencies_[cell_index * kDigitsCount + number] = true;
            
            board[i][j] = number + '0';
            if (recursionSolve(board, i, j)) {
                return true;
            }
            rows_occurencies_[i * kDigitsCount + number] =
            columns_occurencies_[j * kDigitsCount + number] =
            cells_occurencies_[cell_index * kDigitsCount + number] = false;
        }
        board[i][j] = '.';

        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        rows_occurencies_ = std::vector<char>(kBoardSize * kDigitsCount, 0);
        columns_occurencies_ = rows_occurencies_;
        cells_occurencies_ = rows_occurencies_;
        assert(board.size() == kBoardSize);
        assert(board[0].size() == kBoardSize);
        for (size_t i = 0; i < board.size(); ++i) {
            assert(board[i].size() == kBoardSize);
            for (size_t j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == '.') {
                    continue;
                } 
                size_t number = board[i][j] - '0';
                rows_occurencies_[i * kDigitsCount + number] = columns_occurencies_[j * kDigitsCount + number] =
                    cells_occurencies_[getCellIndex(i, j) * kDigitsCount + number] = true;
            }
        }
        recursionSolve(board, 0, 0);
    }
private:
    static constexpr size_t kBoardSize = 9;
    static constexpr size_t kDigitsCount = 10;
    vector<char> rows_occurencies_;
    vector<char> columns_occurencies_;
    vector<char> cells_occurencies_;
};
