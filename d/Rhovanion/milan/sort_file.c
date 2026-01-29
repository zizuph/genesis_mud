void
sort_file(string file)
{
  string read, line, *lines;
  int i,j,changed;
 
  setuid();
  seteuid(getuid());

  changed = 0;
  line = "";
  j = 1;
  read = read_file(file, j, 99);
  if(!read) return;

  lines = ({line}) + explode(read+"\n","\n");
  lines = lines - ({""});
  lines = sort_array(lines);

  while(sizeof(lines) > 1)
  {
    changed = 1;
    for(i=0; i < sizeof(lines)-1; i++)
      if(!write_file(file+".tmp", lines[i]+"\n"))
        write("Couldn't write file '"+file+".tmp'\n");
    line = lines[sizeof(lines)-1];
    
    j += 100;
    read = read_file(file, j, 99);
    if(!read)
    {
      lines = ({ });
      break;
    }
    lines = ({line}) + explode(read+"\n","\n");
    lines = lines - ({""});
    lines = sort_array(lines);
  }

  if(changed)
  {
    if(!rm(file)) write("didn't remove '"+file+"'\n");
    j = 1;
    read = read_file(file+".tmp", j, 99);
    while(read)
    {
      if(!write_file(file, read)) write("Couldn't write file '"+file+"'\n");
      j += 100;
      read = read_file(file+".tmp", j, 99);
    }
    if(!rm(file+".tmp")) write("didn't remove '"+file+".tmp'\n");
  }
}
