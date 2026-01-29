/*
 * This file is to be inherited if you need some fancy functions
 * supporting ranks and some other stuff.    Milan
 */

#define RANKS ({ "Servant","Footman","Standard Bearer","Corporal","Sergeant","Warrant Officer","Lieutenant","Captain" })


/*
 * This will return array (representing ranks) with array of players with
 * given rank.
 */
mixed
select_ranks(object *list)
{
  mixed ranks;
  int i,j;

  ranks = allocate(8);
  for(i=0; i<8; i++)
    ranks[i] = ({ });

  for(i=0; i<sizeof(list); i++)
   if((j=member_array(list[i]->query_s_c_level(), RANKS)) != -1)
     ranks[j] += ({ list[i] });

  return ranks;
}

/*
 * returns rank. -1 mean that it is nonmember
 */
int
get_rank(object obj)
{
  return member_array(obj->query_s_c_level(), RANKS);
}




/*
 * this is from cmd_soul.c   Handy.
 */
static object *
find_neighbour(object *found, object *search, int depth)
{
    int il, im;
    mixed *exit_arr;
    object *new_search, *rooms, troom;

    if (!depth)
        return found;

    rooms = found;
    new_search = ({ });

    for (il = 0; il < sizeof(search); il++)
    {
        exit_arr = (mixed *) search[il]->query_exit();

        for (im = 0; im < sizeof(exit_arr); im += 3)
        {
            if (objectp(exit_arr[im]))
                troom = exit_arr[im];
            else
                troom = find_object(exit_arr[im]);
            if ((troom) && (member_array(troom, rooms) < 0))
            {
                rooms += ({ troom });
                new_search += ({ troom });
            }
        }
    }
    return find_neighbour(rooms, new_search, depth - 1);
}
