#Pyhton Program to create a 2D density Plots from G4CMP file
import csv
import math
class Open_G4CMP_file():
    A="phononTF"

    B="phononTS"
    C="phononL"

    x=[]
    x_i=[]
    y=[]
    y_i=[]
    t_i=[]
    names=[]
    Energy_Deposited=[]
    Start_Energy=[]
    i=0
    z=[]# the final position
    z_i=[]
    t_f=[]





    def __init__(self,nameFile):
        self.nameFile= nameFile


    def GeneratingFiles(self):
        with open(self.nameFile) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            line_count = 0
            list_of_column_names = []

            # loop to iterate through the rows of csv
            for row in csv_reader:

                # adding the first row
                list_of_column_names.append(row)

                # breaking the loop after the
                # first iteration itself
                break


            for lines in csv_reader:
                    #print(lines[9])
                #i=1+i
                #print(i)
                    #Energy_Initial_e.append(float(lines[4]))

                self.Start_Energy.append(float(lines[4]))
                self.x_i.append(float(lines[5])*100)
                self.y_i.append(float(lines[6])*100)
                self.z_i.append(float(lines[7])*100)
                self.t_i.append(float(lines[8]))
                self.Energy_Deposited.append(float(lines[9]))
                self.x.append(float(lines[11])*100)
                self.y.append(float(lines[12])*100)
                self.names.append(lines[3])
                self.t_f.append(float(lines[14]))
                self.z.append(float(lines[13])*100)#Converting to cm from mete


name='phonons_hits.txt'
Custics=Open_G4CMP_file.Open_G4CMP_file(name)
print(Custics.x_i)




# 
#
#
# import plotly
# # import plotly.plotly as py
# import chart_studio.plotly as py
# import plotly.figure_factory as ff
#
# import numpy as np
# import plotly.express as px
# t = np.linspace(-1, 1.2, 2000)
# x = (t**3) + (0.3 * np.random.randn(2000))
# y = (t**6) + (0.3 * np.random.randn(2000))
#
# colorscale = ['#7A4579', '#D56073', 'rgb(236,158,105)', (1, 1, 0.2), (0.98,0.98,0.98)]
#
# fig = ff.create_2d_density(
#     x, y, colorscale=colorscale,
#     hist_color='rgb(255, 237, 222)', point_size=3
# )
#
#
# fig.show()
# #py.iplot(fig, filename='histogram_subplots')
# py.show()

#Accesing to the File with the Phonon Impact on the Sensitive area
