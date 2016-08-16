#include <vector>
#include <string>
#include <stdexcept>
namespace AlgLib
{
    template <typename T>
    Matrix<T>::Matrix(int row, int column) :
        mMatrix(row, AlgLib::Vector<T>(column, T(0))), // creates 0-matrix
        rows(row),
        columns(column)
    {
    }

    template <typename T>
    Matrix<T>::Matrix(const std::vector< std::vector<T> >& theMatrix) :
        rows(theMatrix.size()),
        columns(theMatrix[0].size())
    {
        mMatrix.reserve(rows);

        for(int i = 0; i < (int) theMatrix.size() - 1; i++)
        {
            if(theMatrix[i].size() != theMatrix[i+1].size())
                throw std::invalid_argument("Matrix has inconsistent dimensions");
        }
        for(auto it = theMatrix.begin(); it != theMatrix.end(); ++it)
        {
            mMatrix.push_back(AlgLib::Vector<T>());
            for(auto jt = it->begin(); jt != it->end(); ++jt)
            {
                mMatrix[it - theMatrix.begin()].push_back(*jt);
            }
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const std::vector< AlgLib::Vector<T> >& theMatrix) :
        mMatrix(theMatrix.size()),
        rows(theMatrix.size()),
        columns(theMatrix[0].size())
    {
        for(int i = 0; i < (int) theMatrix.size() - 1; i++)
        {
            if(theMatrix[i].size() != theMatrix[i+1].size())
                throw std::invalid_argument("Matrix has inconsistent dimensions");
        }
        mMatrix = theMatrix;
    }
    template<typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > matrix) :
        rows(matrix.size()),
        columns(matrix.begin()->size())
    {
        // Create matrix
        std::vector< AlgLib::Vector<T> > m;
        int col = matrix.begin()->size();
        for (auto i = matrix.begin(); i != matrix.end(); i++) {
            AlgLib::Vector<T> row;
            row.reserve( i->size() );
            int counter = 0;
            for (auto j = i->begin(); j != i->end(); j++) {
                row.push_back(*j);
                counter++;
            }
            if(counter != col)
                throw std::invalid_argument("Initializer list did not provide rectangular matrix");
            m.push_back(row);
        }
        mMatrix = m;
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix<T>& rhs) :
        mMatrix(rhs.mMatrix)
    {

    }

    template <typename T>
    std::vector< AlgLib::Vector<T> > Matrix<T>::getRowVectors() const
    {
        return mMatrix;
    }

    template <typename T>
    std::vector< AlgLib::Vector<T> > Matrix<T>::getColumnVectors() const
    {
        std::vector< AlgLib::Vector<T> > ret(this->numColumns(), AlgLib::Vector<T>(this->numRows()));
        for (int r = 0; r < this->numRows(); r++)
        {
            for (int c = 0; c < this->numColumns(); c++)
            {
                ret[c][r] = mMatrix[r][c];
            }
        }
        return ret;
    }

    template <typename T>
    void Matrix<T>::setValue(int row, int col, T value)
    {
        if(row >= (int) mMatrix.size() || row < 0 || col < 0 || col >= (int) mMatrix[0].size())
            throw std::out_of_range("Attempted to set value for Matrix out of range");
        mMatrix[row][col] = value;
    }

    template <typename T>
    std::vector<T>& Matrix<T>::operator[](int row)
    {
        return mMatrix[row];
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator+ (const Matrix<T>& other) const
    {
        if(other.mMatrix.size() != mMatrix.size() || other.mMatrix[0].size() != mMatrix[0].size())
            throw std::invalid_argument("Attempted Matrix addition with mismatched dimensions");
        int row = mMatrix.size();
        int col = mMatrix[0].size();

        std::vector< std::vector<T> > retMatrix(row, std::vector<T>(col));
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                retMatrix[i][j] = mMatrix[i][j] + other.mMatrix[i][j];
            }
        }
        return Matrix(retMatrix);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator- (const Matrix<T>& other) const
    {
        if(other.mMatrix.size() != mMatrix.size() || other.mMatrix[0].size() != mMatrix[0].size())
            throw std::invalid_argument("Attempted Matrix addition with mismatched dimensions");
        int row = mMatrix.size();
        int col = mMatrix[0].size();

        std::vector< std::vector<T> > retMatrix(row, std::vector<T>(col));
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                retMatrix[i][j] = mMatrix[i][j] - other.mMatrix[i][j];
            }
        }
        return Matrix(retMatrix);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator* (const Matrix<T>& other) const
    {
        // Jonathan Xia 7/18/16: may implement Strassen's Algorithm later
        if(mMatrix[0].size() != other.mMatrix.size())
            throw std::invalid_argument("Attempted Matrix multiplication with mismatched dimensions");
        std::vector< std::vector<T> > retMatrix(mMatrix.size(), std::vector<T>(other.mMatrix[0].size()));
        for(int r = 0; r < (int) mMatrix.size(); r++)
        {
            for(int c = 0; c < (int) other.mMatrix[0].size(); c++)
            {
                T sum = T(0);
                for(int run = 0; run < (int) mMatrix[0].size(); run++)
                {
                    sum += mMatrix[r][run] * other.mMatrix[run][c];
                }
                retMatrix[r][c] = sum;
            }
        }
        return retMatrix;
    }

    template <typename T>
    int Matrix<T>::numRows() const
    {
        return rows;
    }
    template <typename T>
    int Matrix<T>::numColumns() const
    {
        return columns;
    }

    template <typename T>
    void Matrix<T>::addRow()
    {
        mMatrix.push_back(AlgLib::Vector<T>(this->numRows()));
        rows++;
    }

    template <typename T>
    void Matrix<T>::addColumn()
    {
        for(int i = 0; i < (int)mMatrix.size(); i++)
        {
            mMatrix[i].push_back( T(0) );
        }
        columns++;
    }

    template <typename T>
    T Matrix<T>::getValue(int row, int col) const
    {
        return mMatrix[row][col];
    }

    template <typename T>
    T Matrix<T>::det() const
    {
        // First throw not_square_matrix if not a square matrix
        // Determinants cannot be evaluated for non square matrices
        /*if(mMatrix.size() != mMatrix[0].size())
            throw not_square_matrix;*/

        // If the matrix is 1x1 then we just return the value in that entry!
        if(mMatrix.size() == 1)
            return mMatrix[0][0];

        // Now we do expansion by minors; should replace this algorithm
        int sign = 1;
        T ret = T(0);
        for(int i = 0; i < static_cast<int>(mMatrix.size()); i++)
        {
            //if(mMatrix.size() == 3) std::cout << ret << std::endl;
            ret += this->getValue(0, i) * sign * (this->getMinor(0, i)).det();
            sign *= -1;

        }
        return ret;

    }

    template <typename T>
    Matrix<T> Matrix<T>::getMinor(int i, int j) const
    {
        // Should throw exception if i and j are bad

        std::vector< AlgLib::Vector<T> > copyOfMatrix(mMatrix);
        copyOfMatrix.erase(copyOfMatrix.begin() + i); // erases the i-th row

        // Now to erase the j-th column
        for(int r = 0; r < static_cast<int>(copyOfMatrix.size()); r++)
        {
            copyOfMatrix[r].erase(copyOfMatrix[r].begin() + j);
        }

        return Matrix(copyOfMatrix);
    }

    template <typename T>
    Matrix<T> Matrix<T>::transpose() const
    {
        return Matrix<T>(this->getColumnVectors());
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
    {
        for(int i = 0; i < m.numRows(); i++)
        {
            for(int j = 0; j < m.numColumns(); j++)
            {
                out << m.getValue(i, j) << " ";
            }
            out << std::endl;
        }
        return out;
    }
}