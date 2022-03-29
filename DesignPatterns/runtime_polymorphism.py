class Grand:
    def fun(self):
        print("Grand")
        return

class Parent(Grand):
    def fun(self):
        print("Parent")
        return

class Child(Parent):
    def fun(self):
        print("Child")
        return
    
class Override:
    def main():
        obj = Child()
        obj.fun()
        print("Calling Parent")
        super(Child,obj).fun()
        super(Parent,obj).fun()
        return

Override.main()