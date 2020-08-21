#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>


#if !(defined _POSIX_C_SOURCE)
typedef long int ssize_t;
#endif

/* Viene inclusa solamente nel caso la versione di getline() di POSIX non sia disponibile. */

#if !(defined _POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200809L

#if !(defined SSIZE_MAX)
#define SSIZE_MAX (SIZE_MAX >> 1)
#endif

ssize_t getline(char **pline_buf, size_t *pn, FILE *fin)
{
  const size_t INITALLOC = 16;
  const size_t ALLOCSTEP = 16;
  size_t num_read = 0;

  // Controlla input non nulli
  if ((NULL == pline_buf) || (NULL == pn) || (NULL == fin))
  {
    errno = EINVAL;
    return -1;
  }

  // Alloca buffer
  if (NULL == *pline_buf) {
    *pline_buf = malloc(INITALLOC);
    if (NULL == *pline_buf) {
      return -1;
    }
    else {
      // Dimensioni buffer
      *pn = INITALLOC;
    }
  }

  /* Step through the file, pulling characters until either a newline or EOF. */

  {
    int c;
    while (EOF != (c = getc(fin)))
    {
      num_read++;

      /* Rialloca il buffer se necessita di più spazio */
      if (num_read >= *pn)
      {
        size_t n_realloc = *pn + ALLOCSTEP;
        char * tmp = realloc(*pline_buf, n_realloc + 1); /* +1 per il NULL. */
        if (NULL != tmp)
        {
          *pline_buf = tmp;
          *pn = n_realloc;
        }
        else
        {
          /* Errore di lettura */
          return -1;
        }

        /* Test per overflow. */
        if (SSIZE_MAX < *pn)
        {
          errno = ERANGE;
          return -1;
        }
      }

      /* Aggiunge il carattere al buffer. */
      (*pline_buf)[num_read - 1] = (char) c;

      /* Break se la linea è terminata. */
      if (c == '\n')
      {
        break;
      }
    }

    /* Nel caso terminiamo il file. */
    if (EOF == c)
    {
      errno = 0;
      return -1;
    }
  }

  /* Carattere NULL per terminare la striga */
  (*pline_buf)[num_read] = '\0';

  return (ssize_t) num_read;
}

#endif