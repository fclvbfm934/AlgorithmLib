#include<stdexcept>
namespace AlgLib
{

    template <typename cont, typename T>
    int binarysearch(cont A, T key)
    {
        int index = 0;
        int sizeofcont = A.size();
        int power = 1; // This will store a power of 2
        if(key < A[0])
        {
            return -1;
        }
        while(power < sizeofcont)
        {
            power *= 2;
        }
        power /= 2; // Power is now the largest power of 2 < sizeofcont

        // power will be chopped in half until it is 0
        // basically, we are going to find the base-2 representation of index
        while(power > 0)
        {
            if(index + power < sizeofcont && A[index + power] > key)
            {
                // This means that we set the digit in index to 0
                power /= 2;
            }
            else if(index + power < sizeofcont && A[index + power] < key)
            {
                // We add power to index so that we mark that digit as a 1
                index += power;
                power /= 2;
            }
            else if(index + power < sizeofcont && A[index + power] == key)
            {
                //Success!!
                return index+power;
            }
            else
            {
                // This means index + power exceeded the maximum size
                // We therefore must decrease the power of 2
                power /= 2;
            }
        }
        // If element not found, this indicates between which indices it would be between
        return -index - 2;
    }
}
