# MNIST Neural Network in C

## Snippet to save and visualise the images
```c
    train_data_t* train_data = (train_data_t*)malloc(sizeof(train_data_t));
    test_data_t* test_data = (test_data_t*)malloc(sizeof(test_data_t));
    mnist_load_data(train_data, test_data);
    for (size_t i = 0; i < 50; i++)
    {
        pgm_save_image(train_data->images[i].data);
    }
```

### [TODO]
Create tests for matrixes, i.e.
```c
    matrix_t* mm = matrix_create(30, 1);
    for (size_t i = 0; i < mm->rows; i++)
    {
        for (size_t j = 0; j < mm->cols; j++)
        {
            mm->data[(i*mm->cols)+j] = rand_norm();
        }
        
    }

    for (size_t i = 0; i < mm->rows; i++)
    {
        for (size_t j = 0; j < mm->cols; j++)
        {
            double val = mm->data[(i*mm->cols) + j];
            printf("%f ", val);
        }
        printf("\n");
        
    }
    
    
    matrix_destroy(mm);
```

## References
[MNIST dataset](http://yann.lecun.com/exdb/mnist/)<br>
[PGM File Format](https://netpbm.sourceforge.net/doc/pgm.html)<br>
[Neural Networks](http://neuralnetworksanddeeplearning.com)