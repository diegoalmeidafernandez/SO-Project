void revList(char *dir) {
    struct dirent *entry;
    DIR *d = opendir(dir);

    if (d != NULL) {
        printf("**************%s\n", dir);
        for (entry = readdir(d); entry != NULL; entry = readdir(d)) {
            char path[1024];
            struct stat info;

            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

                if (stat(path, &info) == 0 && S_ISDIR(info.st_mode)) {
                        revList(path);
                    }
                } else {
                    perror("Error obteniendo información del archivo.\n");
                }
            }
    }else {
        perror("Error obteniendo el directorio.\n");
    }

    rewinddir(d);

    for (entry = readdir(d); entry != NULL; entry = readdir(d)) {
        char path[1024];
        struct stat info;

        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

            if (stat(path, &info) == 0) {
                    printf("%8ld \t %s\n", info.st_size, entry -> d_name);
            }else {
                perror("Error obteniendo la información.\n");
            }
        }
    }
    closedir(d);
}

