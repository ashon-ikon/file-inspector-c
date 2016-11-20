# Some code usages

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
