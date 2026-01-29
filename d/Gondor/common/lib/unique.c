/*
 * Function name: clone_special
 * Description	: Use this function to clone a limited number
 *		  of a certain object, and once that number
 *		  is reached, begin cloning alternate objects.
 * Arguments	: string file - The file path to the main object.
 *		  int    num  - The max number of copies of the
 *				main object allowed.
 *		  mixed alt   - If this is a simple string filepath,
 *				the object of the filepath will try
 *				to always be cloned as an alternate.
 *		 	      - If an array, it should be an array
 *				of mixed array's that contain filepath
 *				and a chance % of that alternate being
 *				chosen.
 */
public varargs object
clone_special(string file, int num = 1, mixed alt = 0)
{
    object ob;
    int    sz, ran, ix;

    if (!strlen(file))
    {
	return ob;
    }

    /* Make sure we have the correct permissions. */
    setuid();
    seteuid(getuid());

    /* Make sure the file we need to test can load. */
    file->load_it();

    /* Find out how many clones we have out there. */
    sz = sizeof(object_clones(find_object(file)));

    if (sz <= num)
    {
	/* We are under the limit, clone the good item. */
	return ob = clone_object(file);
    }

    if (stringp(alt))
    {
	/* Alternate was a file reference, try to clone it. */
	return ob = clone_object(alt);
    }

    if (pointerp(alt))
    {
	sz = sizeof(alt);
	if (!sz)
	{
	    return ob;
	}

	/* Give a random chance out from 1-99 for failure. */
	ran = random(99) + 1;
	if (sz == 1)
	{
	    if (!pointerp(alt[0]))
	    {
		if (!stringp(alt[0]))
		{
		    /* Can people not read instructions? */
		    return ob;
		}
		/* This is just in case people don't adhere to form. */
		return ob = clone_object(alt[0]);
	    }
	}

	ix = -1;
	while(++ix < sz)
	{
	    if (sizeof(alt[ix]) != 2)
	    {
		/* We need two arguments, file and chance. */
		continue;
	    }

	    if (alt[ix][1] > ran)
	    {
		/* We have a winner, try cloning it. */
		ob = clone_object(alt[ix][0]);
		break;
	    }
	}
    }
    /* Return item or 0 as appropriate. */
    return ob;
}
