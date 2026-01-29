/*
 * /d/Gondor/common/guild2/books/purge_library.c
 *
 * A feature that lacks in the library code is to remove the files of books
 * that are removed or replaced. The function in this file will perform a
 * check and remove books that are not associated.
 *
 * To operate: Call the routine purge_library in this file.
 *
 * Make a backup of the library before you do so!
 *
 * Created by Mercade, 6 May 2004
 */

#include "../lib/morgul_defs.h"

#define BOOKS_DIR         (GUILD_DIR + "books/")
#define MAGE_BOOKS_DIR    (BOOKS_DIR + "mages/")
#define NAZGUL_BOOKS_DIR  (BOOKS_DIR + "nazgul/")

#define MAGE_BOOK_INDEX   (BOOKS_DIR + "mage_library")
#define NAZGUL_BOOK_INDEX (BOOKS_DIR + "nazgul_library")
#define OPEN_BOOK_INDEX   (BOOKS_DIR + "open_library")
#define SUBMISSIONS_INDEX (BOOKS_DIR + "submissions")

#define PATHS_INDEX "paths"
#define BOOKS_INDEX "books"
#define SUBM_INDEX  (1)

void
purge_library()
{
    mapping book_index;
    string *files;
    string *books;
    string  filename;
    int     index;
    int     deleted;
    
    setuid();
    seteuid(getuid());

    /* Processing mage library directory. */

    books = ({ });
    /* Restore mage book index. */
    book_index = restore_map(MAGE_BOOK_INDEX);
    if (!m_sizeof(book_index))
    {
        write("Failed to restore: " + MAGE_BOOK_INDEX + "\n");
        return;
    }
    books += book_index[PATHS_INDEX];
    /* Restore open book index. */
    book_index = restore_map(OPEN_BOOK_INDEX);
    if (!m_sizeof(book_index))
    {
        write("Failed to restore: " + OPEN_BOOK_INDEX + "\n");
        return;
    }
    books += book_index[PATHS_INDEX];
    /* Restore submissions index. */
    book_index = restore_map(SUBMISSIONS_INDEX);
    if (!m_sizeof(book_index))
    {
        write("Failed to restore: " + SUBMISSIONS_INDEX + "\n");
        return;
    }
    book_index = book_index[BOOKS_INDEX];
    if (!m_sizeof(book_index))
    {
        write("Error in " + BOOKS_INDEX + " in: " + SUBMISSIONS_INDEX + "\n");
        return;
    }
    files = m_indices(book_index);
    for (index = 0; index < sizeof(files); index++)
    {
        books += ({ book_index[files[index]][SUBM_INDEX] });
    }

    deleted = 0;
    files = get_dir(MAGE_BOOKS_DIR + "book*");
    write("Found " + sizeof(files) + " books in " + MAGE_BOOKS_DIR + "\n");
    for (index = 0; index < sizeof(files); index++)
    {
        filename = MAGE_BOOKS_DIR + files[index];
        if (member_array(filename, books) == -1)
        {
            rm(filename);
            deleted++;
        }
    }
    write("Deleted " + deleted + " unassociated books.\n");

    /* Processing nazgul library directory. */

    books = ({ });
    /* Restore nazgul book index. */
    book_index = restore_map(NAZGUL_BOOK_INDEX);
    if (!m_sizeof(book_index))
    {
        write("Failed to restore: " + NAZGUL_BOOK_INDEX + "\n");
        return;
    }
    books += book_index[PATHS_INDEX];

    deleted = 0;
    files = get_dir(NAZGUL_BOOKS_DIR + "book*");
    write("Found " + sizeof(files) + " books in " + NAZGUL_BOOKS_DIR + "\n");
    for (index = 0; index < sizeof(files); index++)
    {
        filename = NAZGUL_BOOKS_DIR + files[index];
        if (member_array(filename, books) == -1)
        {
            rm(filename);
            deleted++;
        }
    }
    write("Deleted " + deleted + " unassociated books.\n");
}
