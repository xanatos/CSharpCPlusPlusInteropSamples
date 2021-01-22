using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CSharpSide
{
    public static class MyClass
    {
        public static void TestAll()
        {
            // We can call instance methods, but we can't use the vtable. So no polymorphism. 

            {
                // base class creation, base method invocation
                Console.WriteLine("C#, NewMyClass");
                IntPtr ptr = Native.NewMyClass(10);
                int value1 = MyClassGetAndIncrement(ptr, 20);
                int value2 = MyClassGetAndIncrement(ptr, 40);
                Native.DeleteMyClass(ptr);
                Console.WriteLine($"C#, NewMyClass, MyClassGetAndIncrement = {value1}, MyClassGetAndIncrement = {value2}");
            }

            {
                // derived class creation, base method invocation
                Console.WriteLine("C#, NewDerivedMyClass");
                IntPtr ptr = Native.NewDerivedMyClass(10);
                int value1 = MyClassGetAndIncrement(ptr, 20);
                int value2 = MyClassGetAndIncrement(ptr, 40);
                Native.DeleteMyClass(ptr);
                Console.WriteLine($"C#, NewDerivedMyClass, MyClassGetAndIncrement = {value1}, MyClassGetAndIncrement = {value2}");
            }

            {
                // derived class creation, override method invocation
                Console.WriteLine("C#, NewDerivedMyClass");
                IntPtr ptr = Native.NewDerivedMyClass(10);
                int value1 = DerivedMyClassGetAndIncrement(ptr, 20);
                int value2 = DerivedMyClassGetAndIncrement(ptr, 40);
                Native.DeleteMyClass(ptr);
                Console.WriteLine($"C#, NewDerivedMyClass, DerivedMyClassGetAndIncrement = {value1}, DerivedMyClassGetAndIncrement = {value2}");
            }

            {
                // static method call
                Console.WriteLine("C#, MyClassNewMyClass");
                IntPtr ptr = MyClassNewMyClass(10);
                int value1 = MyClassGetAndIncrement(ptr, 20);
                int value2 = MyClassGetAndIncrement(ptr, 40);
                Native.DeleteMyClass(ptr);
                Console.WriteLine($"C#, MyClassNewMyClass, MyClassGetAndIncrement = {value1}, MyClassGetAndIncrement = {value2}");
            }
        }

        public static IntPtr MyClassNewMyClass(int value)
        {
            return Environment.Is64BitProcess ? Native.MyClassNewMyClass64(value) : Native.MyClassNewMyClass32(value);
        }

        public static int MyClassGetAndIncrement(IntPtr ptr, int incr)
        {
            return Environment.Is64BitProcess ? Native.MyClassGetAndIncrement64(ptr, incr) : Native.MyClassGetAndIncrement32(ptr, incr);
        }

        public static int DerivedMyClassGetAndIncrement(IntPtr ptr, int incr)
        {
            return Environment.Is64BitProcess ? Native.DerivedMyClassGetAndIncrement64(ptr, incr) : Native.DerivedMyClassGetAndIncrement32(ptr, incr);
        }

        public static class Native
        {
            [DllImport(@"CPlusPlusSide")]
            public static extern IntPtr NewMyClass(int value);

            [DllImport(@"CPlusPlusSide")]
            public static extern IntPtr NewDerivedMyClass(int value);

            [DllImport(@"CPlusPlusSide")]
            public static extern void DeleteMyClass(IntPtr cl);

            // EntryPoint generated with DUMPBIN /exports CPlusPlusSide.dll
            [DllImport(@"CPlusPlusSide", EntryPoint = "?NewMyClass@MyClass@@SGPAV1@H@Z", ExactSpelling = true)]
            public static extern IntPtr MyClassNewMyClass32(int value);

            // EntryPoint generated with DUMPBIN /exports CPlusPlusSide.dll
            [DllImport(@"CPlusPlusSide", EntryPoint = "?NewMyClass@MyClass@@SAPEAV1@H@Z", ExactSpelling = true)]
            public static extern IntPtr MyClassNewMyClass64(int value);

            // EntryPoint generated with DUMPBIN /exports CPlusPlusSide.dll
            [DllImport(@"CPlusPlusSide", CallingConvention = CallingConvention.ThisCall, EntryPoint = "?GetAndIncrement@MyClass@@UAEHH@Z", ExactSpelling = true)]
            public static extern int MyClassGetAndIncrement32(IntPtr cl, int inc);

            // EntryPoint generated with DUMPBIN /exports CPlusPlusSide.dll
            [DllImport(@"CPlusPlusSide", CallingConvention = CallingConvention.ThisCall, EntryPoint = "?GetAndIncrement@MyClass@@UEAAHH@Z", ExactSpelling = true)]
            public static extern int MyClassGetAndIncrement64(IntPtr cl, int inc);

            // EntryPoint generated with DUMPBIN /exports CPlusPlusSide.dll
            [DllImport(@"CPlusPlusSide", CallingConvention = CallingConvention.ThisCall, EntryPoint = "?GetAndIncrement@DerivedMyClass@@UAEHH@Z", ExactSpelling = true)]
            public static extern int DerivedMyClassGetAndIncrement32(IntPtr cl, int inc);

            // EntryPoint generated with DUMPBIN /exports CPlusPlusSide.dll
            [DllImport(@"CPlusPlusSide", CallingConvention = CallingConvention.ThisCall, EntryPoint = "?GetAndIncrement@DerivedMyClass@@UEAAHH@Z", ExactSpelling = true)]
            public static extern int DerivedMyClassGetAndIncrement64(IntPtr cl, int inc);
        }
    }
}
