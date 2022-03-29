## Factory Design Pattern:

from abc import abstractstaticmethod, ABCMeta, abstractclassmethod
import cv2

# design an abstract parent class. - only interfaces.
class IImageProcessor(metaclass=ABCMeta):

    @abstractclassmethod
    def reader(self):
        print("abstract reader method call")
        pass

    @abstractstaticmethod
    def  processor(self):
        pass

    @abstractstaticmethod
    def writer(self):
        pass



class ImageSharpener(IImageProcessor):
    def __init__(self):
        self.path = 'Image path'
        self.data = None
        self.output = None
    # must implement reader, processor and writer methods.
    def reader(self):
        print("Reading")        
        print("self.data = cv2.imread(self.path) \n")
        # cv2.imread(self.path)
    def processor(self):
        print("Processing")
        print("self.output = cv2.sharpen(self.data) \n")

    # not implementing write       
    def writer(self):
        print("Writing")
        print("cv2.write(writepath, self.output) \n")

    def shape(self):
        print("shape : 10,10")


class Brightener(IImageProcessor):
    def __init__(self):
        self.path = 'Image path'
        self.data = None
        self.output = None
    # must implement reader, processor and writer methods.
    def reader(self):
        print("Reading")        
        print("self.data = cv2.imread(self.path) \n")
        # cv2.imread(self.path)
    def processor(self):
        print("Processing")
        print("self.output = cv2.Brighten(self.data) \n")

    # not implementing write       
    def writer(self):
        print("Writing")
        print("cv2.write(writepath, self.output) \n")

    def shape(self):
        print("shape : 10,10")



# print(ImageSharpener().shape())
print(Brightener)