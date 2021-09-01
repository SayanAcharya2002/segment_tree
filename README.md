# segment_tree
This is a library for all of one's segment tree related needs. comes loaded with lazy propagation, build, update, search capabilities
# How to use
  There are both the options of lazy and non lazy versions in the constructor. by changing the bool value of the laziness variable that can be controlled. also a default value for the lazy array can be supplied as well. After construction of the class, 2 or 4 pointers (depending on the laziness) have to be set. that can be done using set_segmenter_class();set_lazy_update_class();set_lazy_stack_class();set_normal_update_class(); functions. Now the way to provide the arguements is a bit different ( due to the wide usage variety of segment trees). It internally uses a functor. So a class has to be provided in the template. Now there are some ready made classes that I have provided namely: segmenter_max, lazy_update_max etc. these have the exact same job as their name suggests. One can write their own classes as well, just make sure to inherit the base abstract classes namely: segmenter_class,lazy_update_class,lazy_stack_class,normal_update_class and define the () operator.
Now the fucntors have this kind of logic in the actual code:
the segmenter_class takes care of what happens when two segments are encountered in the build operation, whether max is to be taken or min is supposed to be taken
the normal_update_class takes care of how to update elements in non-lazy mode.
the lazy_update_class takes care of what happens when a node is lazily updated. like how the changes to that node should be committed.
the lazy_stack_class takes care of how to stack lazy_updates one after the other but does not directly commit the changes.
for the build operation a pointer has to be provided to signify the main array that will be used throughout. different allocation is not done. rather the pointer provided will be used as the main array.

For more details, please see the tutorial_main.cpp.

Please let me know if there are errors or bugs in the code.
