#To Print To A File:   make windows > C:/Users/*******/Desktop/Out.txt 2>&1

WinGPP = g++
LinGPP = g++

BinDIR = bin
ObjDIR = obj
SrcDIR = src
BitFLG = -m32
WinOUT = OpenGL32_x$(subst -m,,$(BitFLG)).dll
LinOUT = OpenGL32_x$(subst -m,,$(BitFLG)).so
WinDIR = $(BinDIR)#/Windows
LinDIR = $(BinDIR)#/Linux
WinLIB = $(SrcDIR)/Imaging
LinLIB = $(SrcDIR)/Imaging
ObjSRC = $(ObjDIR)#/$(subst -m,,$(BitFLG))

WinDEP = -static -static-libgcc -static-libstdc++ -shared -s -Wl,--enable-stdcall-fixup -o
LinDEP = -static -static-libgcc -static-libstdc++ -shared -s -Wl,--enable-stdcall-fixup -o

WinARGS = -std=c++11 -Wall -pedantic -O3 -DOPENGL32_EXPORTS -s -c $(BitFLG)
LinARGS = -std=c++11 -Wall -pedantic -O3 -DOPENGL32_EXPORTS -s -c $(BitFLG)
	
CppFiles = \
	$(wildcard $(SrcDIR)/Hooks/*.cpp) \
	$(wildcard $(WinLIB)/*.cpp)
	
ObjFiles = \
	$(patsubst $(SrcDIR)/%.cpp,$(ObjSRC)/%.o,$(CppFiles))
	
all:
	@echo
	@echo "  Instructions For Making OpenGL32:"
	@echo
	@echo "    For Windows:   	make windows"
	@echo "    For Linux:      	make linux"
	@echo "    For Both:       	make both"
	@echo "    To Clean Files: 	make clean"
	
everything: linux windows

linux:
ObjSRC = obj/Lin$(subst -m,,$(BitFLG))
linux:$(LinDIR)/$(LinOUT)

windows:
ObjSRC = obj/Win$(subst -m,,$(BitFLG))
windows : $(WinDIR)/$(WinOUT)
	@echo
	@echo "Finished Building OpenGL32."
	
clean:
	@echo "    Cleaning Build Files."
	@rm -rf $(ObjFiles) $(BinDIR) $(ObjDIR)

$(WinDIR)/$(WinOUT): $(ObjFiles)
	@echo
	@echo "Linking Object Files.."
	@mkdir -p $(WinDIR)
	@$(WinGPP) -Wl,--kill-at -d --input-def $(SrcDIR)/OpenGL32.def $(WinDEP) $(WinDIR)/$(WinOUT) $(ObjFiles) $(BitFLG) -lgdi32 -lglu32 -lopengl32
	
$(ObjSRC)/%.o: $(SrcDIR)/%.cpp
	@echo "    Compiling: " $<
	@mkdir -p $(ObjSRC)
	@mkdir -p $(ObjSRC)/Imaging
	@mkdir -p $(ObjSRC)/Hooks
	@$(WinGPP) $(WinARGS) -o $@ $<