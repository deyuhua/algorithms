/*
 * Auhtor: deyuhua, email: deyuhua@gmail.com  
 * This header provide some base functions that most often used.
 */

/*
 * C don't provide boolean value, so define bool as enum type
 */
typedef enum {false=0, true} bool;

/*
 * sfree means that free dynamic memory saftly.
 */
void sfree (void * ptr)
{
    if (ptr){
        free (ptr);
        ptr = NULL;
    }
}

/*
 * smalloc means that allocate dynamic memory saftly.
 */
void * smalloc (size_t size)
{
    void * ptr;
    if (!(ptr = malloc (size))){
        perror("Can't allocate dynamic memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/*
 * same as smalloc, srealloc means that realloc dynamic memory saftly;
 */
void * srealloc (void * old_ptr, size_t size)
{
    void * ptr;
    if (!(ptr = realloc (old_ptr, size))){
        perror("Can't reallocate dynamic memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
