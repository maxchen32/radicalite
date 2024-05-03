add_rules("mode.debug", "mode.release")

includes("@builtin/xpack")

if is_mode("debug") then
	add_defines("DEBUG")
	set_symbols("debug")
	set_warnings("all")
elseif is_mode("release") then
	set_strip("all")
end

if not is_os("windows") then
	add_syslinks("m")
end

target("objs")
	set_kind("object")
	set_warnings("all")
	add_includedirs("include", {public = true})
	add_files("src/*.c")
	add_cflags("-fPIC")

target("radicalite_static")
	set_kind("static")
	set_warnings("all")
	add_deps("objs")
	set_basename("radical")
	set_prefixname("lib")
	set_targetdir("$(buildir)/lib")


target("radicalite_shared")
	set_kind("shared")
	set_warnings("all")
	add_deps("objs")
	set_basename("radical")
	set_prefixname("lib")
	set_targetdir("$(buildir)/lib")

target("headers")
	set_kind("headeronly")
	add_headerfiles("include/(*.h)") 

local examples = {"eyyc", "xyline", "sin-cos", "eyyc_new", "simple_vector_calcs"}
if is_mode("debug") then
	table.insert(examples, "test")
end
for i,filename in pairs(examples) do
	target(filename)
		set_kind("binary")
		add_files("examples/"..filename..".c")
		set_default(false)
		set_warnings("all")
		add_deps("radicalite_shared")
		add_linkdirs("$(buildir)/lib")
		add_links("radical")
		add_rpathdirs(".")
		add_rpathdirs("/usr/lib")
		add_rpathdirs("/usr/local/lib")
		add_rpathdirs("@executable_path")
		set_targetdir("$(buildir)/examples")
end

xpack("pack")
    set_formats("zip")
	set_basename("radicalite-$(plat)")
	add_targets("radicalite_static")
	add_targets("radicalite_shared")
	add_targets(examples)
	add_targets("headers")
	add_installfiles("(LICENSE)")
	add_installfiles("(README.md)")
	add_installfiles("(docs/**)")
    