target("radical") 
    set_kind("static")
    add_includedirs("include")
    add_files("src/*.c")

target("radical_shared")
	set_kind("shared")
	add_includedirs("include")
	add_files("src/*.c")
	set_basename("radical")

local tests = {"eyyc", "xyline", "sin-cos"}
for i,filename in pairs(tests) do
	target(filename)
		set_kind("binary")
		add_includedirs("include")
		add_files("examples/"..filename..".c")
		add_deps("radical")
end
