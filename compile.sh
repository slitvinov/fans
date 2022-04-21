$HOME/basilisk/src/qcc -autolink 3d.c -DDUMBGL -grid=octree -O3 -lm \
		       -L$HOME/basilisk/src/gl \
		       -lglutils -lfb_glx `pkg-config --libs glew x11` 

# 		       -L$HOME/basilisk/src/gl -lfb_dumb  -lfb_glx  -lfb_osmesa  
