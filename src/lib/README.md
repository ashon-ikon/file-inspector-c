# Some code usages

## Standard Array
Standard arrays can be used to in a flexible manner.

### Simple arrays
For simple applications where shallow coping is just enough:
```C
// An array of simple floats
struct FiArray *arr = fi_array_new(sizeof(float), NULL);

float t = 0.0L;

for(t = 100.0;  t < 110.0; t += 1.0)
    fi_array_push(arr, &t);

for(int i = 0; i < 10; i++) {
    float *var = fi_array_get_ptr_next(arr, float);
    if (var)
        printf("Got %f\n", *var);
}
fi_array_free(arr);

```
### Advanced array needs
For applications that require custom copy method/ deep copying
```C
typedef struct person_st {
    char *name;
} Person;

bool person_copy (void const *src, void *dst, unsigned n)
{
    // check src && dst
    ((Person *)dst)->name = fi_strdup(((Person *)src)->name );
    
    return true;
}

void cleanup_notify (struct FiArray *arr)
{
    Person *student;
    // Loop through and clean up
    fi_array_each(arr, Person, student) {
        free(student->name);
    }
}

// An array for complex structures

Person student;
student.name = fi_strdup("James");

struct FiArray *arr = fi_array_new(sizeof(Person), person_copy);

fi_array_set_cleanup_notifier(arr, cleanup_notify);

fi_array_push(arr, &student);

free(student.name);

Person *p_student = fi_array_get_ptr_being(arr, Person);

printf("Hello %s\n", p_student->name); 

fi_array_free(arr);


```

## File Containers
This is an array of file meta which can easily grow dynamically as needed.

### Sample Container Code
```C
// Create the container 
struct FiFileContainer *con = fi_file_container_init();
struct FiFileInfo file, file2;
 
// Initialize the file meta. [Always preferred]
fi_file_init(&file);
fi_file_init(&file2);

// Add files information to the container
fi_file_container_push(con, &file);
fi_file_container_push(con, &file2);

// Loop through the file container
struct FiFileInfo *file = NULL;
fi_container_each(con, file) {
      // Use "file"
}
    
// Free the container
fi_file_container_destroy(con);
```

Pretty straight forward
