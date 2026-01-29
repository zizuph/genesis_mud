/*
 * This is the same as /lib/cache.c, but only caches one file.
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

/*
 * These global variables are private and static. They will not be saved
 * and are invisible to inheriting objects.
 */
static private mapping data = ([ ]);
static private string   cache_file  = 0;
static private int      cache_tries = 0;
static private int      cache_hits  = 0;

/*
 * Function name: in_cache
 * Description  : Call this function to find out whether the contents of a
 *                particular data file is in the cache.
 * Arguments    : string filename - the filename to check.
 * Returns      : int 1/0 - true if the data file is in the cache.
 */
nomask static int
in_cache(string filename)
{
    return (cache_file == filename);
}

/*
 * Function name: read_cache
 * Description  : This function is the real cache. It takes the filename of
 *                the data file as argument and if the information is not
 *                found in the cache, it is read from disk and stored in the
 *                cache for later reference. To use the cache, just replace
 *                call to the efun restore_map() to the lfun read_cache().
 *                The arguments and return values are exactly the same.
 * Arguments    : string filename - the filename to read.
 * Returns      : mapping - the data file read from the save-file or ([ ]) in
 *                          case of an error.
 */
nomask static mapping
read_cache(string filename)
{
    /* Count the number of tries to the cache. */
    cache_tries++;

    /* Remove the trailing ".o" if it is added to the path. */
    sscanf(filename, "%s.o", filename);

    /* See whether the information with that name is already in the
     * cache. Yes, HIT, no load == cpu saved!
     */
    if (cache_file == filename)
    {
	/* Count the number of hits in the cache. */
	cache_hits++;

	/* Return the cached information, that is... a copy of it. */
        return secure_var(data);
    }

    /* The information is apparently not in the cache. Read the file from
     * disk. In case of an error, return the empty mapping. This will
     * probably not happen because even if you try to restore a non-existant
     * mapping, the efun restore_map will return an empty mapping. *duh*
     */
    if (catch(data = restore_map(filename)) ||
	!mappingp(data))
    {
	data = ([ ]);
    }

    /* Add the read information to the cache. */
    cache_file = filename;

    /* Return the read information, that is... a copy of it. */
    return secure_var(data);
}

/*
 * Function name: save_cache
 * Description  : When information that is in the cache is saved, then not
 *                only the information on disk should be changed, but the
 *                information in the cache should be altered too. The
 *                arguments to this function are exactly the same as to
 *                the efun save_map(). This function does NOT cache on the
 *                save, i.e. when the data is not in the cache when it is
 *                saved, it will not be added to the cache. However, in
 *                practice I don't think a file will ever be saved without
 *                being in the cache.
 * Arguments    : mapping data     - the data to save.
 *                string  filename - the filename to save to.
 */
nomask static void
save_cache(mapping newdata, string filename)
{
    /* Remove the trailing ".o" if there is one. */
    sscanf(filename, "%s.o", filename);

    /* If the entry is in the cache, update it. */
    if (in_cache(filename))
    {
        data = secure_var(newdata);
    }

    /* Save the information as usual. */
    save_map(data, filename);
}

/*
 * Function name: rm_cache
 * Description  : When you remove a file that is currently in the cache,
 *                you should use this function rather than the efun rm()
 *                in order to remove the information from the cache too.
 *                If you fail to do this, the information will remain in
 *                the cache while the original file does not exist anymore.
 *                The argument and return value are exactly the same as
 *                those of the efun rm().
 * Arguments    : string filename - the filename to remove.
 * Returns      : int 1/0 - the return value from the efun rm.
 */
nomask static int
rm_cache(string filename)
{
    /* Remove the trailing ".o" if there is one. */
    sscanf(filename, "%s.o", filename);

    if(cache_file == filename)
    {
        cache_file = 0;
        data = ([ ]);
    }

    /* Remove the file as usual. */
    return rm(filename + ".o");
}

/*
 * Function name: remove_from_cache
 * Description  : It may be necessary to remove a data file from the cache.
 *                This function does that for you. An example of a situation
 *                in which this is necessary is if you want to rename a
 *                data file that is in the cache, for there is no cache
 *                version of the efun rename() because of implementational
 *                difficulties. There is no return function because it will
 *                always succeed.
 * Arguments    : string filename - the filename to remove.
 */
nomask static int
remove_from_cache(string filename)
{
    /* Remove the trailing ".o" if there is one. */
    sscanf(filename, "%s.o", filename);

    if(cache_file == filename)
    {
        cache_file = 0;
        data = ([ ]);
    }
}

/*
 * Function name: reset_cache
 * Description  : This function will flush the cache and remove all data
 *                files from it. This will save memory, but has no other
 *                effects. The cache size will not be reset.
 */
nomask static void
reset_cache()
{
    data = ([ ]);
    cache_file = 0;
}

/*
 * Function name: query_cache
 * Description  : This will return an array containing the file names of all
 *                data files stored in the cache. The list is sorted, with
 *                the data file most recently queried is on top of the array,
 *                etcetera.
 * Returns      : string * - an array with the file names of all data files
 *                           stored in the cache.
 */
nomask static string *
query_cache()
{
   return ({ secure_var(cache_file) });
}

/*
 * Function name: cache_report
 * Description  : To get a very small report on the efficiency of the cache,
 *                call this function. The results will be printed with write().
 */
nomask public void
cache_report()
{
    write(sprintf("Cache tries %6d\nCache hits  %6d\nHit ratio   %6d%%\n",
	cache_tries, cache_hits, ((cache_hits * 100) / cache_tries)));
}
