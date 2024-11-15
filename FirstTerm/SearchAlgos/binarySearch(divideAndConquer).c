int binarySearch(int arr[], int size, int item)// O(log2(n)
{
    int left = 0;
    int right = size - 1;
    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        if (item == arr[middle])
        {
            return middle;
        }
        if (item < arr[middle])
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    return -1;
}