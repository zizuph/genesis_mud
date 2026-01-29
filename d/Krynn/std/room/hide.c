/*    /d/Krynn/std/room/hide.c
 *
 */

static mapping	gTerrain = ([
				"road" : 40,
				"path" : 35,
				"forest" : 10,
				"plain" : 20
			   ]);

nomask public void
calc_room_hide()
{
    mixed *strarr, short;
    int size, t1, t2, minimum;

    if (!stringp(short = query_short()))
	return;

    strarr = explode(short, " ");
    strarr = (m_indexes(gTerrain) & strarr);

    size = sizeof(strarr);

    if (size)
    {
	if (size > 1)
	{
	    t1 = gTerrain[strarr[0]];
	    t2 = gTerrain[strarr[1]];
	    minimum = MIN(t1, t2);
	    t1 = (ABS(t1 - t2)/2) + minimum;
	    add_prop(ROOM_I_HIDE, t1);
	}
	else
	    add_prop(ROOM_I_HIDE, gTerrain[strarr[0]]);
    }
}

