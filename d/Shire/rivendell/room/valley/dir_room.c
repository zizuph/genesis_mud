/*
 * Directional room.
 *
 *
 * This room may have different descriptions, depending from which
 * direction the player entered the room.
 *
 * See the accompaining doc file for details.
 *
 * Written by Fysix
 * Borrowed by Finwe 
 */
 
inherit "std/room";
 
mapping origins = ([]);
mapping phrases = ([]);
 
 
enter_inv(object obj, object origin)
{
  if (obj && origin)
    origins[obj] = file_name(origin);
  
  return ::enter_inv(obj, origin);
}
 
 
leave_inv(object obj, object destination)
{
  if (obj)
    m_delete(origins, obj);
 
  return ::enter_inv(obj, destination);
}
 
 
string dir_phrase(string label)
{
  object player;
  string origin;
  string phrase;
  
  if ((player = this_interactive()) == 0)
    return "";
 
  if ((origin = origins[player]) != 0 && 
      (phrase = phrases[label + ":" + origin]) != 0)
    return phrase;
 
  if ((phrase = phrases[label]) != 0)
    return phrase;
  
  return "";
}
 
 
void add_dir_phrase(string label, string origin, string phrase)
{
  if (label && origin)
    phrases[label + ":" + origin] = phrase;
  if (label)
    phrases[label] = phrase;
}
