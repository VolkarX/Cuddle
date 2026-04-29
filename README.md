# Cuddle

**⚠️ AVERTISSEMENT : Ce programme est un projet Epitech. Il est strictement interdit de le réutiliser, de le cloner ou de s'en inspirer pour un de vos rendus académiques sous peine de sanctions pour plagiat (cheat).**

## 📝 Description

**Cuddle** is a C library for data manipulation and analysis, strongly inspired by pandas in Python. It provides a `dataframe_t` structure and a set of utility functions to read, process, and extract statistics from dataset files (CSV).

## 🛠️ Compilation

Instructions de compilation non trouvées.

## 🚀 Utilisation

Here is a quick example of how to use the Cuddle library in your own C programs:

```c
#include "./include/dataframe.h"

int main(void)
{
    // 1. Read a CSV file into a DataFrame
    dataframe_t *df = df_read_csv("data.csv", ",");
    if (!df)
        return (84);

    // 2. Get the shape of the DataFrame
    dataframe_shape_t s = df_shape(df);
    printf("--- SHAPE ---\nRows: %d, Cols: %d\n\n", s.nb_rows, s.nb_columns);

    // 3. Convert a column to a specific type
    df_to_type(df, "age", INT);

    // 4. Display general information about the DataFrame
    printf("--- INFO ---\n");
    df_info(df);

    // 5. Display statistical descriptions of the numeric columns
    printf("\n--- DESCRIBE ---\n");
    df_describe(df);

    // 6. Write the modified DataFrame to a new CSV
    df_write_csv(df, "output.csv");

    // 7. Free the allocated memory
    df_free(df);

    return (0);
}
```

## 📋 📋 Features

- **I/O Operations:** Read and write CSV files dynamically with type deduction.
- **Data Inspection:** View the shape of the dataset, print general information, describe basic statistics (sum, min, max, etc.), and view the head/tail of the data.
- **Data Manipulation:**
  - `df_sort`: Sort datasets based on a specific column.
  - `df_filter`: Filter rows using a custom boolean function.
  - `df_apply`: Apply a transformation function to all values of a column.
  - `df_groupby`: Aggregate data by unique values in a column.
  - `df_to_type`: Downcast or change the type of a column's data.
## 📋 📋 Build

You can build the project using the provided `Makefile`:

```bash
make
```

Ensure you have a standard C compiler (like `gcc`) and `make` installed on your system.
## 📋 📋 Supported Column Types

The library automatically detects and supports various column types:
- `BOOL`
- `INT`
- `UINT`
- `FLOAT`
- `STRING`
- `UNDEFINED`
## 📋 📋 Disclaimer

This repository is for educational purposes. Please respect Epitech's policy on cheating and code sharing.