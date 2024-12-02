int linearSearch(int arr[], int size, int item) // O(n)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == item)
        {
            return i;
        }
    }
    return -1;
}