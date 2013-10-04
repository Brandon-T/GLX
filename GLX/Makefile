#To Print To A File:   make windows > C:/Users/*******/Desktop/Out.txt 2>&1

WinGPP = g++
LinGPP = g++

BinDIR = bin
ObjDIR = obj
SrcDIR = src
BitFLG = -m32
WinOUT = GLX$(subst -m,,$(BitFLG)).dll
LinOUT = GLX$(subst -m,,$(BitFLG)).so
WinDIR = $(BinDIR)#/Windows
LinDIR = $(BinDIR)#/Linux
ObjSRC = $(ObjDIR)#/$(subst -m,,$(BitFLG))

WinDEP = -static -static-libgcc -static-libstdc++ -shared -s -o
LinDEP = -static -static-libgcc -static-libstdc++ -shared -s -o

WinARGS = -std=c++11 -Wall -pedantic -O3 -DGLX_EXPORTS -s -c $(BitFLG)
LinARGS = -std=c++11 -Wall -pedantic -O3 -DGLX_EXPORTS -s -c $(BitFLG)
	
CppFiles = \
	$(wildcard $(SrcDIR)/*.cpp)
	
ObjFiles = \
	$(patsubst $(SrcDIR)/%.cpp,$(ObjSRC)/%.o,$(CppFiles))
	
all:
	@echo
	@echo "  Instructions For Making GLX:"
	@echo
	@echo "    For Windows:   	make windows"
	@echo "    For Linux:      	make linux"
	@echo "    For Both:       	make both"
	@echo "    To Clean Files: 	make clean"
	@echo "    Specific Builds: BitFLG=-m32 | BitFLG=-m64"
	
both: linux windows

linux:
ObjSRC = obj/Lin$(subst -m,,$(BitFLG))
linux:$(LinDIR)/$(LinOUT)

windows:
ObjSRC = obj/Win$(subst -m,,$(BitFLG))
windows : $(WinDIR)/$(WinOUT)
	@echo
	@echo "Finished Building GLX."
	
clean:
	@echo "    Cleaning Build Files."
	@rm -rf $(BinDIR) $(ObjDIR)

$(WinDIR)/$(WinOUT): $(ObjFiles)
	@echo
	@echo "Linking Object Files.."
	@mkdir -p $(WinDIR)
	@$(WinGPP) $(WinDEP) $(WinDIR)/$(WinOUT) $(ObjFiles) $(BitFLG)
	
$(ObjSRC)/%.o: $(SrcDIR)/%.cpp
	@echo "    Compiling: " $<
	@mkdir -p $(ObjSRC)
	@$(WinGPP) $(WinARGS) -o $@ $<