#include <iostream>
#include <set>

/**
 * Finds pairs in an array that sum to a specified value using brute force.
 * Iterates over every possible pair to check their sum.
 * 
 * @param arr Array of integers.
 * @param len Length of the array.
 * @param value Target sum value for pairs.
 */
void bruteForce(int arr[], int len, int value) {
    // Iterate over array elements.
    for (int i = 0; i < len; ++i) {
        // Check every pair combination.
        for (int j = i + 1; j < len; ++j) {
            // If pair sums to value, print it.
            if (arr[i] + arr[j] == value) {
                std::cout << arr[i] << '+' << arr[j] << '=' << value << '\n';
                return;
            }
        }
    }

    std::cout << "No result.\n";
}

/**
 * Finds pairs in an array that sum to a specified value using dynamic programming.
 * Utilizes a set to track seen numbers, optimizing the search process.
 * 
 * @param arr Array of integers.
 * @param len Length of the array.
 * @param value Target sum value for pairs.
 */
void dp(int arr[], int len, int value) {
    std::set<int> seenNumbers; // Tracks numbers already seen.

    // Iterate over array elements.
    for (int i = 0; i < len; ++i) {
        int diff = value - arr[i]; // Calculate needed difference for sum.
        
        // If difference has been seen, a pair exists.
        if (seenNumbers.contains(diff)) {
            // Print the pair.
            std::cout << diff << '+' << arr[i] << '=' << value << '\n';
            return;
        }
        // Insert current number into seenNumbers set.
        seenNumbers.insert(arr[i]);
    }

    std::cout << "No result.\n";
}

/**
 * Main function to demonstrate finding pairs with brute force and DP.
 */
int main(void) {
    int arr[] = {1,2,3,4,5,6,7,8}; // Example array.
    int len = 8; // Array length.

    // Demonstrate brute force approach.
    std::cout << "Brute Force Approach:\n";
    bruteForce(arr, len, 15);

    // Demonstrate dynamic programming approach.
    std::cout << "\nDynamic Programming Approach:\n";
    dp(arr, len , 15);
}
