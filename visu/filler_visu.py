import tkinter as tk
import time
import re
import sys
from tkinter import *
from PIL import Image, ImageTk
from tkinter.font import Font

WINDOW_HEIGHT = 800
WINDOW_WIDTH = WINDOW_HEIGHT + 300

COLOR_P1 = "red"
COLOR_P2 = "yellow"

global PAUSED

class FrameMap():
	def __init__(self, window_ctrl, rows, columns):
		self.window_ctrl = window_ctrl
		self.rows = rows
		self.columns = columns
		self.frame = tk.Frame(self.window_ctrl.window)
		self.frame.pack(side="left")
		self.map_data = {}

		self.cell_size = (WINDOW_HEIGHT - 8) / (self.rows if self.rows > self.columns else self.columns)
		self.map_canvas = tk.Canvas(self.frame)
		self.map_canvas.configure(width=(self.cell_size * self.columns),
								height=(self.cell_size * self.rows))
		self.map_canvas.configure(background='black')
		self.map_canvas.pack(side="left")
		for column in range(self.columns):
			for row in range(self.rows):
				x1 = column * self.cell_size+4
				y1 = row * self.cell_size+4
				x2 = x1 + self.cell_size
				y2 = y1 + self.cell_size
				self.map_data[row, column] = self.map_canvas.create_rectangle(x1, y1, x2, y2, fill="black")

class FrameResult():
	def __init__(self, window_ctrl, p1, p2):
		self.window_ctrl = window_ctrl
		self.p1 = p1
		self.p2 = p2
		
		self.frame = tk.Frame(self.window_ctrl.window)
		self.frame.configure(background='black')
		self.frame.pack()


		if WINDOW_HEIGHT > 600:
			load = Image.open('visu/filimage.png')
			render = ImageTk.PhotoImage(load)
			img = tk.Label(self.frame, image=render, borderwidth=0)
			img.image = render
			img.pack(pady=50)
			font = Font(family="Helvetica", size=20, weight="bold")
		else:
			
			font = Font(family="Helvetica", size=15, weight="bold")



		label = tk.Label(self.frame, text=f"{self.p1.name}", fg = f"{self.p1.color}", font = font, justify='center', bg='black').pack()
		self.score_p1 = tk.StringVar()
		self.score_p1.set(f'{0}%')
		tk.Label(self.frame, textvariable = self.score_p1, fg = f"{self.p1.color}", font = font, justify='center', bg='black').pack()

		self.score_res = tk.StringVar()
		self.score_res.set(f'{0}')
		num = int(self.score_res.get())
		tk.Label(self.frame, textvariable = self.score_res, fg = f"{self.p1.color}", font = font, justify='center', bg='black').pack()
		if self.p2:
			label = tk.Label(self.frame, text=f"\nVS\n", fg='white', font = font, justify='center', bg='black').pack()

			label = tk.Label(self.frame, text=f"{self.p2.name}", fg = f"{self.p2.color}", font = font, justify='center', bg='black').pack()

			self.score_p2 = tk.StringVar()
			self.score_p2.set(f'{0}%')
			tk.Label(self.frame, textvariable = self.score_p2, fg = f"{self.p2.color}", font = font, justify='center', bg='black').pack()
			self.score_res1 = tk.StringVar()
			self.score_res1.set(f'{0}')
			num1 = int(self.score_res1.get())
			tk.Label(self.frame, textvariable = self.score_res1, fg = f"{self.p2.color}", font = font, justify='center', bg='black').pack()
		else:
			self.score_p2 = None

class WindowController():
	def __init__(self, player1, player2):
		self.window = tk.Tk()
		self.window.title(f'Filler : {player1.name} vs {player2.name}')
		try:
			index = int(sys.argv[2])
			ws = self.window.winfo_screenwidth()
			hs = self.window.winfo_screenheight()
			
			ws -= ws % WINDOW_WIDTH
			hs -= hs % WINDOW_HEIGHT

			max_index = (ws / WINDOW_WIDTH) * (hs / WINDOW_HEIGHT)
			if index <= max_index:
				x = (index * WINDOW_WIDTH) % ws
				y = int((index * WINDOW_WIDTH) / ws) * (WINDOW_HEIGHT + 45)
				self.window.geometry('%dx%d+%d+%d' % (WINDOW_WIDTH, WINDOW_HEIGHT, x, y))
			else:
				self.window.geometry(f"{WINDOW_WIDTH}x{WINDOW_HEIGHT}")
		except Exception as e:
			self.window.geometry(f"{WINDOW_WIDTH}x{WINDOW_HEIGHT}")

		self.window.configure(background='black')

	def start_loop(self):
		self.window.mainloop()

class Player():
	def __init__(self, id, line):
		self.id = id
		self.name = re.match(r"^.*\[(.*)\].*$", line).group(1).split("/")[-1].replace("a.out","default").replace(".filler","")

		if self.id == 1:
			self.char = 'O'
			self.color = COLOR_P1
		else:
			self.char = 'X'
			self.color = COLOR_P2

		self.score = 0

class GameController():
	def __init__(self, rows, columns, p1, p2=None):
		self.p1 = p1
		self.p2 = p2
		self.rows = rows
		self.columns = columns
		self.res = 0
		self.res1 = 0
		self.aff = 0
		self.window_ctrl = WindowController(p1, p2)
		self.window_ctrl.window.bind("<Button-1>", self.put_in_pause)
		self.window_ctrl.window.bind("<Return>", self.go_next_step)

		self.map = FrameMap(self.window_ctrl, rows, columns)
		self.result = FrameResult(self.window_ctrl, p1, p2)

		if WINDOW_HEIGHT < 600:
			font = Font(family="Helvetica", size=15, weight="bold")
		else:
			font = Font(family="Helvetica", size=30, weight="bold")

		self.final = tk.StringVar()
		self.final.set(f'')
		self.final_label = tk.Label(self.result.frame, textvariable = self.final, fg = f"white", font = font, justify='center', bg='black')
		self.final_label.pack()

	def start(self):
		self.window_ctrl.window.after(1, self.loop_read)
		self.window_ctrl.start_loop()

	def put_in_pause(self, nooo):
		global PAUSED
		PAUSED = not PAUSED

	def go_next_step(self, nooo):
		if PAUSED:
			self.next_step()

	def loop_read(self):
		if PAUSED:
			self.window_ctrl.window.after(100, self.loop_read)
		else:
			res = self.next_step()
			if res == "finish":
				# print("FINISH")
				return
			self.window_ctrl.window.after(1, self.loop_read)

	def next_step(self):
		line = ""
		while "Plateau" not in line:
			try:
				line = input()
				if "== O fin:" in line:
					return ("finish")
			except:
				return ("bug")
		if "Plateau" in line:
			input()
			self.update_grid()
			return("updated")
		return("none")
	def update_grid(self):
		o = 0
		x = 0
		for row in range(self.map.rows):
			line = input()[4:]
			for column in range(self.map.columns):
				if line[column] in 'ox':
					if line[column] == 'o':
						p = self.p1
						o = 1
					else:
						p = self.p2
						x = 1
					if self.map.map_canvas.itemcget(self.map.map_data[row, column], "fill") != p.color:
						self.map.map_canvas.itemconfig(self.map.map_data[row, column], fill=p.color)
						p.score += 1

						if line[column].lower() == 'o':
							self.result.score_p1.set(f"Map conquis = {int(p.score/(self.rows*self.columns)*100)}%")
						else:
							self.result.score_p2.set(f"Map conquis = {int(p.score/(self.rows*self.columns)*100)}%")
						self.window_ctrl.window.update_idletasks()
		if o == 1:
			self.res += 1
			self.result.score_res.set(f"Score = {self.res}")
			if self.res - (self.res1 + 1) == 2:
				if self.p1.name == "nboulif":
					self.final_label.config(fg="green")
				else:
					self.final_label.config(fg="gray")
				self.final_label.pack()
				self.final.set(f"Winner = {self.p1.name}")
		else:
			self.res1 += 1
			self.result.score_res1.set(f"Score = {self.res1}")
			if self.res1 - (self.res + 1) == 2:
				if self.p2.name == "nboulif":
					self.final_label.config(fg="green")
				else:
					self.final_label.config(fg="gray")
				self.final_label.pack()
				self.final.set(f"Winner = {self.p2.name}")

if __name__ == '__main__':
	if  len(sys.argv) > 1:
		try:
			wh = int(sys.argv[1])
			if wh <= 1000 and wh >= 200:
				WINDOW_HEIGHT = wh
				WINDOW_WIDTH = WINDOW_HEIGHT + 300
		except Exception as e:
			pass
	line = ""
	p1 = None
	p2 = None
	while "Plateau" not in line:
		line = input()
		if "$$$ exec p1 :" in line:
			p1 = Player(1, line)
		elif "$$$ exec p2 :" in line:
			p2 = Player(2, line)
	if "Plateau" not in line:
		print("NO PLATEAU")
		exit()
	PAUSED = False
	d = line[:-1].split(" ")
	rows= int(d[1])
	columns = int(d[2])
	the_game = GameController(rows, columns, p1, p2)
	the_game.start()
