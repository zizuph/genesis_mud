static mapping nomination_map = ([]);

#define SAVE_FILE "/d/Krynn/morrigan/save"

void create()
{
  setuid();
  seteuid(getuid());
  
  nomination_map = restore_map(SAVE_FILE);
}

/* add a nomination...
 * returns -1 on error, 0 if nominee already nominated by
 * nominator, 1 if successful.
 */
int add_nomination(mixed nominator, mixed nominee)
{
  string *current_nominations;

  if (objectp(nominator))
  {
    nominator = nominator->query_real_name();
  }

  if (!stringp(nominator))
  {
    return 0;
  }

  if (objectp(nominee))
  {
    nominee = nominee->query_real_name();
  }

  if (!stringp(nominee))
  {
    return 0;
  }

  current_nominations = nomination_map[nominator];
  if (!current_nominations)
  {
    current_nominations = ({ });
  }
  else if (member_array(nominator, current_nominations) >= 0)
  {
    return 0;
  }

  current_nominations += ({ nominator });
  nomination_map[nominee] = current_nominations;
 
  setuid();
  seteuid(getuid());
  save_map(nomination_map, SAVE_FILE);
  
  return 1;
}

/* remove a nomination.
 * returns -1 on error, returns 0 if no nomination exists,
 * returns 1 on success.
 */
int remove_nomination(mixed nominator, mixed nominee)
{
  string *current_nominations;

  if (objectp(nominator))
  {
    nominator = nominator->query_real_name();
  }

  if (!stringp(nominator))
  {
    return -1;
  }

  if (objectp(nominee))
  {
    nominee = nominee->query_real_name();
  }

  if (!stringp(nominee))
  {
    return -1;
  }

  current_nominations = nomination_map[nominator];
  if (!current_nominations)
  {
    return 0;
  }

  if (member_array(nominator, current_nominations) >= 0)
  {
    return 0;
  }

  current_nominations -= ({ nominee });
  nomination_map[nominee] = current_nominations;
 
  setuid();
  seteuid(getuid());
  save_map(nomination_map, SAVE_FILE);
  
  return 1;
}  

/* clear all nominations of a given nominee.
 * returns -1 on error, 0 if no nominations exist,
 * 1 on success.
 */
int clear_nomination(mixed nominee)
{
  if (objectp(nominee))
  {
    nominee = nominee->query_real_name();
  }

  if (!stringp(nominee))
  {
    return -1;
  }

  if (member_array(nominee, m_indices(nomination_map)) < 0)
  {
    return 0;
  }

  nomination_map = m_delete(nomination_map, nominee);

  setuid();
  seteuid(getuid());
  save_map(nomination_map, SAVE_FILE);
  
  return 1;
}

/* get the array of nominators for a nominee
 * returns 0 on error an array of names otherwise.
 */
string *query_nomination(mixed nominee)
{
  if (objectp(nominee))
  {
    nominee = nominee->query_real_name();
  }

  if (!stringp(nominee))
  {
    return 0;
  }

  if (!pointerp(nomination_map[nominee]))
  {
    return ({ });
  }

  return nomination_map[nominee];
}

/* return how many nominations a nominee has
 * returns -1 on error, number of nominations otherwise
 */
int query_number_nominations(mixed nominee)
{
  if (objectp(nominee))
  {
    nominee = nominee->query_real_name();
  }

  if (!stringp(nominee))
  {
    return -1;
  }

  if (!pointerp(nomination_map[nominee]))
  {
    return 0;
  }

  return sizeof(nomination_map[nominee]);
}

  
