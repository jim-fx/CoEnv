<script lang="ts">
	import { Hexagon } from '.';
	export let animated = false;
</script>

<div relative center>
	<h1
		text-center
		w-full
		absolute
		text-black
		text-8xl
		font-bolder
		style="top: 50%; transform: translateY(-50%); z-index: 2;"
	>
		CoEnv
	</h1>
	<div class:animated absolute w-full h-full style="transform:scale(1.1)">
		<Hexagon --fill="none" --stroke="white" --stroke-width="5px" />
	</div>
	<div absolute w-full h-full>
		<Hexagon --fill="white" --stroke="none" --stroke-width="5px" />
	</div>
</div>

<style>
	.animated {
		animation: booink 20s cubic-bezier(0.8, -0.02, 0.27, 0.99) infinite;
	}

	@keyframes booink {
		0% {
			transform: scale(1) rotate(0deg);
		}
		5% {
			transform: scale(1.3) rotate(0deg);
		}
		10% {
			transform: scale(1.3) rotate(180deg);
		}

		15% {
			transform: scale(1) rotate(180deg);
		}

		100% {
			transform: scale(1) rotate(180deg);
		}
	}
</style>
