from tkinter import *
from tkinter.ttk import *
import ctypes

def setup_root(bg, size, h_board):
	root = Tk()
	root.config(background=bg)
	root.title("_.~\"~._.~\"~._.~\"~._.~\"~._Filler.~\"~._.~\"~._.~\"~._.~\"~._")
	root.geometry(size)
	height = h_board
	return root

def setup_boardC(root, size, bg):
	boardFrame = Canvas(root)
	boardFrame.config(background=bg)
	boardFrame.place(height=size, width=size, relx=0.5, rely=0.5, anchor=CENTER)
	return boardFrame

def setup_pieceC(parent, bg):
	width = 300;
	height = 100;
	num_sqrs = 8
	pieceCanv = Canvas(parent)
	pieceCanv.config(background=bg, relief=RAISED, highlightbackground="white")
	pieceCanv.place(rely=0.115, relx=0.15, height=height, width=width)
	grid = print_board(num_sqrs, width, pieceCanv)
	return grid, pieceCanv

def setup_menuC(root, height, width, bg):
	menuFrame = Canvas(root)
	menuFrame.config(background=bg, relief=RAISED, highlightbackground="white")
	menuFrame.place(height=height, width=width, x=250, relx=0.9, rely=0.5, anchor="e")

	button1 = Button(menuFrame, text="pause")
	button2 = Button(menuFrame, text="next")
	button1.place(relx=0.15)
	button2.place(relx=0.60)

	labelPiece = Label(menuFrame, text="Current piece:", foreground=bg)
	labelPiece.config(background=bg, foreground='blue')
	labelPiece.place(rely=0.1, relx=0.15) # relx=0.36

	grid, pieceCanv = setup_pieceC(menuFrame, bg)
	return menuFrame, pieceCanv, grid

def print_board(size, height, boardFrame):
	grid = [ [1]*(size+1) for n in range(size+1) ]
	w = height/size
	y = 0
	for row in grid:
		x = 0
		for col in row:
			boardFrame.create_rectangle(x, y, x+w, y+w, outline='red')
			x = x+w
		y = y+w
	return grid

def change_color(x, y, w, color, boardFrame):
	boardFrame.create_rectangle(x*w, y*w, x*w+w, y*w+w, fill=color, outline='red')

def main():
	height = 1350
	bg = "black"
	root = setup_root(bg, "5120x2880", height)
	boardFrame = setup_boardC(root, height, bg)

	size = 50
	grid_b = print_board(size, height-3, boardFrame)

	w = (height-3)/size
	change_color(0, 0, w, "blue", boardFrame)

	menuFrame, pieceCanv, grid_p = setup_menuC(root, height, 600, bg)
	change_color(0, 0, 300/8, "blue", pieceCanv)

	# NUM = 2
	# fun = ctypes.CDLL(test.so)
	# fun.test.argtypes(ctypes.c_int)
	# returnVale = fun.test(NUM)
	# print(returnVale)
	# pieceCanv.delete("all")
	root.mainloop()

if __name__== "__main__":
  main()
