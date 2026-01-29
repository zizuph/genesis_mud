
varargs string home(string whose)
{
  object master;

  master = find_object("secure/master");

  if (!whose) 
    whose = this_interactive()->query_real_name();
  return master->query_wiz_path(whose);
}


string pwd()
{
  return this_interactive()->query_path();
}


static object defaultenv(object env)
{
  return (env ? env : environment(this_interactive()));
}

static string expand_path(string str)
{
  string a, b;
  
  if (!str)                        return 0;
  if (sscanf(str, "/%s", a))       return str;
  if (sscanf(str, "~/%s", a))      return home() + "/" + a;
  if (sscanf(str, "~%s/%s", a, b)) return home(a) + "/" + b;
  return pwd() + "/" + str;
}



status match_object(object obj, string str)
{
  string fname, tmp;

  if (!obj) return 0;
  if (obj->id(str)) return 1;
  
  fname = file_name(obj);
  str = expand_path(str);
  
  if (fname == str) return 1;
  if (sscanf(fname, str + "#%s", tmp)) return 1;
  
  return 0;
}


static object *get_objects(string str, object env)
{
  object *objs;

  if (!str) return 0;

  objs = filter(all_inventory(defaultenv(env)), 
		"match_object", this_object(), str);
  if (sizeof(objs) > 0)
    return objs;

  if (str == "users" && env == 0)     return users();
  return 0;
}


static object get_object(string str, object env)
{
  object obj;
 
  if (!str) return 0;
  if ((obj = present(str, defaultenv(env))) != 0) return obj;
  if ((obj = find_object(expand_path(str))) != 0) return obj;
  if ((obj = find_living(lower_case(str)))  != 0) return obj;

  if (str == "here")  return environment(env ? env : this_interactive());
  if (str == "me")    return            (env ? env : this_interactive());
}


object *locate_objects(string str, object env)
{
  string a,b;
  object *objs, obj;
  
  if (!str) 
    return 0;

  if (sscanf(str, "%s:%s", a, b))
    return locate_objects(b, get_object(a, env));
  
  if ((objs = get_objects(str, env)) != 0)  return objs;
  if ((obj  = get_object(str, env))  != 0)  return ({ obj });
  
  return 0;
}


object *locate_objs_load_files(string arg)
{
  object *objs;
  string filename;
  object obj;

  if ((objs = locate_objects(arg, 0)) != 0 &&
      sizeof(objs) > 0) {
    return objs;
  }

  if ((filename = expand_path(arg)) != 0 &&
      file_size(filename + ".c") >= 0) {

    catch(call_other(filename, "???"));

    if ((obj = find_object(filename)) != 0) 
      return ({ obj });
    else
      write ("** Error loading '" + filename + "'.\n");
  }
  
  return 0;
}



mixed *locate_objs_or_files(string arg)
{
  object *objs;
  string filename;

  if ((objs = locate_objects(arg, 0)) != 0 &&
      sizeof(objs) > 0) {
    return objs;
  }

  if ((filename = expand_path(arg)) != 0 &&
      file_size(filename + ".c") >= 0) {

    return ({ filename });
  }

  
  return 0;
}




int make_object(string filename)
{
  object obj;

  if ((obj = clone_object(filename)) != 0) {
    switch (obj->move(this_interactive())) {
    case 1:
    case 6:
      obj->move(environment(this_interactive()), 1);
      break;
    case 2:
    case 3:
    case 4:
    case 5:
      obj->move(this_interactive(), 1);
      break;
    }
    return 1;
  } else {
    notify_fail("Could not clone: " + filename +"\n");
    return 0;
  }
}


