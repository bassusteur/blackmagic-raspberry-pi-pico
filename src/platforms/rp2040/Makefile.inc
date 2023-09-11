BUILD_DIR = ./platforms/rp2040/build

make:
	make command.c
	if [ ! -d $(BUILD_DIR) ]; then \
		mkdir $(BUILD_DIR); \
	fi;
	cd $(BUILD_DIR)
	cmake ./platforms/rp2040 -B $(BUILD_DIR)
	make -C $(BUILD_DIR)

