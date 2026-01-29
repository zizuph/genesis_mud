#pragma save_binary

void
sort_file(string file)
{
  string foobar, text, *lines = ({ });
  int i,j;
 
  if(sscanf(file, "%s.%s",foobar, foobar) == 2)
  {
    write("For safety reason this will work only on files without '.'.\n");
    return;
  }

  seteuid(getuid());

  i = 1;
  text = read_file(file, i, 1);
  if(!text || strlen(text)<1) return;

  while(strlen(text) > 0)
  {
    i += 1;
    lines += ({ text });
    text = read_file(file, i, 1);
  }
  lines = sort_array(lines);

  if(!rm(file))
  {
    write("didn't remove '"+file+"'\n");
    return;
  }

  for(i=0; i < sizeof(lines); i++)
    if(!write_file(file, lines[i]))
    {
      write("Couldn't write file '"+file+"'\n");
      return;
    }
}