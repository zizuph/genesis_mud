#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include "defs.h"

private mapping files = ([
   // id : filename
]);
private mapping names = ([
   // id : name
]);
private mapping ids = ([
   // filename : id
]);
private mapping name_ids = ([
   // name : ({ id1, id2, id3, ... })
]);

private int max_id = 0;

public void
create()
{
    setuid();
    seteuid(getuid());
    restore_object(GARDENER_HERBS);
}

public int
add_herb(object herb)
{
   string file = HERB_FILE(herb), name;
   int id;

   if(ids[file])
   {
      return 0;
   }

   name = herb->query_herb_name();
   id = ++max_id;
   files[id] = file;
   names[id] = name;
   ids[file] = id;

   if(!name_ids[name])
   {
      name_ids[name] = ({ id });
   } else {
      name_ids[name] += ({ id });
   }

   save_object(GARDENER_HERBS);
   return secure_var(id);
}

public int
query_herb_id(object herb)
{
   string file = HERB_FILE(herb);

   if(!ids[file])
   {
      return 0;
   }

   return secure_var(ids[file]);
}

public int
query_file_id(string file)
{
   if(!ids[file])
   {
      return 0;
   }

   return secure_var(ids[file]);
}

public string
query_id_file(int id)
{
   if(!files[id])
   {
      return 0;
   }

   return secure_var(files[id]);
}

public int *
query_name_ids(string name)
{
   if(!name_ids[name])
   {
      return 0;
   }

   return secure_var(name_ids[name]);
}

public int
query_id_name(int id)
{
   if(!names[id])
   {
      return 0;
   }

   return secure_var(names[id]);
}
