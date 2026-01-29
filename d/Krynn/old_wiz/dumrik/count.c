// Count.c
//
// Coded by Dumrik         1995-09-28   00:21
//
// A counter that counts the number of players in each domain
// this is NOT i repeat NOT an exercise in structured programming
//
///Dumrik


#include "/d/Krynn/common/defs.h"

inherit R_FILE

create_room()
{
  set_short("A counting room");
  set_long("Do a count\n");
  
}

int
init()
{
  ::init();
  ADA("count");
}


/*
   function: space
   desc: Generates a certain number of spaces
   arg: number of spaces to generate
*/

string
space(int n)
{
  int i;
  string result = "";
  
  for(i=0;i<n;i++) result = result + " ";

  return result;
}     

/*
   function: sort_func
   desc: a helpfunction to sort_array()
   arg: 2 strings that are to be compared
*/


int
sort_func(string a,string b) 
{
  int c,d;

  c = atoi(explode(a,"#")[0]);
  d = atoi(explode(b,"#")[0]);

  if (c==d) return 0;

  if (c > d)
    return -1;
  else
    return 1;
}

/*
   function: sort_map
   desc: sort a mapping on the second column of the array that the mapping contains
   arg: the mapping to be sorted
*/
   
string *
sort_map(mapping map)
{
  string *array_to_sort, *tmp_array;
  int i;

  array_to_sort = ({ });
  tmp_array = m_indexes(map);

  for(i=0;i<sizeof(tmp_array);i++) {
    array_to_sort += ({ sprintf("%d",map[tmp_array[i]][0]) + "#" +
      sprintf("%d",map[tmp_array[i]][1]) + "#" + tmp_array[i] });
  }
 
  sort_array(array_to_sort,"sort_func",TO);

  return array_to_sort;
}


/*
   function: left_just
   desc: Left justifies a string or int in a field with a certain width
   arg: the width of the field and the string/int to be justified
*/

string
left_just(int width, mixed str)
{
  string str2;
  
  str2 = str;
  if (intp(str)) str2 = sprintf("%d",str);
  return (str2 + space(width - strlen(str2)));
}

/*
   function: right_just
   desc: does the same as left_just() but as the name implies right justifies instead
   arg: the same as left_just()
*/

string
right_just(int width, mixed str)
{
  string str2;

  str2 = str;
  if (intp(str)) str2 = sprintf("%d",str);
  return (space(width - strlen(str2)) + str2);
}


/*
   function: display_map
   desc: displays the mapping to the player
   arg: an array (its a hack....sue me :-))
*/

int
display_map(string *tmp_array) 
{
  int i;
  string *temp;

  write("  Domain               #Mortals   #Wizards\n");
  write("==========================================\n");
  
  for(i=0;i<sizeof(tmp_array);i++) {
    temp = explode(tmp_array[i],"#");
    write(right_just(3,(i + 1) + ".") + " " + left_just(15,temp[2]) +
	  right_just(10,temp[0]) + right_just(10,temp[1]) + "\n");
  }

  write("==========================================\n");
}


/*
   function: count
   desc: does the work with counting the players and puts them in the right place in a
         mapping.
   arg: nothing
*/


int
count()
{
  object *people, room;
  int wiz = 0;
  int mortal = 0;
  int i;
  string domain;
  mapping map = ([ ]);
  string *sorted_stuff = ({ });

  
  people = users();


  for(i=0;i<sizeof(people);i++) {
    room = environment(people[i]);
    if (objectp(room)) domain = explode(file_name(room),"/")[2];
    if (!pointerp(map[domain])) map+= ([ domain : ({ 0, 0 }) ]);

    if (people[i]->query_wiz_level()) {
      wiz++;
      map[domain][1]++;
    } else {
      mortal++;
      map[domain][0]++;
    }   
  }

  sorted_stuff = sort_map(map);
  display_map(sorted_stuff);
  write("    " + left_just(15,"Total:") + right_just(10,mortal) +
	right_just(10,wiz) + right_just(10,wiz+mortal) + "\n");
  
  return 1;
}











